"""Bounded loopback checks for the additional networking reference lessons."""
from contextlib import contextmanager
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer
import json
import os
from pathlib import Path
import queue
import shutil
import socket
import ssl
import struct
import subprocess
import tempfile
import threading

ROOT = Path(__file__).resolve().parents[3]
BASE = ROOT / 'build/additions/networking'
REPORT = ROOT / 'build/networking-reference-checks'
RESULTS = []


def binary(lesson, name='main'):
    return BASE / lesson / (name + ('.exe' if os.name == 'nt' else ''))


def run(path, *args, success=True):
    process = subprocess.run([str(path), *map(str, args)], cwd=ROOT, capture_output=True, text=True, timeout=10)
    assert (process.returncode == 0) == success, (path, process.returncode, process.stdout, process.stderr)
    return process


def passed(name):
    RESULTS.append(name)
    print('PASS', name, flush=True)


@contextmanager
def service(server):
    worker = threading.Thread(target=server.serve_forever)
    worker.start()
    try:
        yield server.server_address[1]
    finally:
        server.shutdown()
        worker.join(5)
        server.server_close()
        assert not worker.is_alive()


class Reply(BaseHTTPRequestHandler):
    protocol_version = 'HTTP/1.1'
    def do_GET(self):
        body = b'authenticated' if isinstance(self.connection, ssl.SSLSocket) else b'local'
        if isinstance(self.connection, ssl.SSLSocket):
            assert self.connection.getpeercert(), 'client identity missing'
        self.send_response(200)
        self.send_header('Content-Length', str(len(body)))
        self.end_headers()
        self.wfile.write(body)
    def log_message(self, *_):
        pass


def certificates(folder):
    def openssl(*args):
        subprocess.run(['openssl', *args], cwd=folder, check=True, capture_output=True, timeout=30)
    openssl('req', '-x509', '-newkey', 'rsa:2048', '-nodes', '-days', '1', '-subj', '/CN=Lesson CA',
            '-keyout', 'ca.key', '-out', 'ca.pem')
    for name, cn, usage in (('server', 'localhost', 'serverAuth'), ('client', 'lesson-client', 'clientAuth')):
        openssl('req', '-newkey', 'rsa:2048', '-nodes', '-subj', '/CN=' + cn,
                '-keyout', name + '.key', '-out', name + '.csr')
        (folder / (name + '.ext')).write_text('extendedKeyUsage=' + usage + '\n'
            + ('subjectAltName=DNS:localhost\n' if name == 'server' else ''))
        openssl('x509', '-req', '-in', name + '.csr', '-CA', 'ca.pem', '-CAkey', 'ca.key',
                '-CAcreateserial', '-days', '1', '-extfile', name + '.ext', '-out', name + '.pem')
    openssl('req', '-x509', '-newkey', 'rsa:2048', '-nodes', '-days', '1', '-subj', '/CN=Untrusted',
            '-keyout', 'bad.key', '-out', 'bad.pem')


def receive_exact(connection, length):
    result = b''
    while len(result) < length:
        chunk = connection.recv(length - len(result))
        if not chunk:
            raise AssertionError('unexpected EOF')
        result += chunk
    return result


def packet(connection):
    header = receive_exact(connection, 1)[0]
    length = 0
    multiplier = 1
    for _ in range(4):
        value = receive_exact(connection, 1)[0]
        length += (value & 127) * multiplier
        assert length <= 4096
        if value < 128:
            return header, receive_exact(connection, length)
        multiplier *= 128
    raise AssertionError('bad remaining length')


def main():
    REPORT.mkdir(parents=True, exist_ok=True)
    bash = 'C:/msys64/usr/bin/bash.exe' if os.name == 'nt' else shutil.which('bash')
    script = ROOT / 'scripts' / ('build-windows.sh' if os.name == 'nt' else 'build-linux.sh')
    lessons = ('02-subnets-and-routing', '19-auth-and-mtls', '26-backpressure-and-rate-limits',
               '27-load-balancing', '21-http-multiplexing', '29-mqtt-delivery', '30-protocol-testing')
    for lesson in lessons:
        for source in sorted((ROOT / 'additions/networking' / lesson).glob('main*.cpp')):
            subprocess.run([bash, str(script), str(source)], cwd=ROOT, check=True,
                           capture_output=True, timeout=180)
    for lesson, names in (('02-subnets-and-routing', ('main', 'main2')),
                          ('26-backpressure-and-rate-limits', ('main',)),
                          ('27-load-balancing', ('main',)), ('29-mqtt-delivery', ('main',)),
                          ('30-protocol-testing', ('main',))):
        for name in names:
            run(binary(lesson, name))
            passed(lesson + '/' + name)
    with tempfile.TemporaryDirectory(dir=REPORT) as directory:
        folder = Path(directory)
        certificates(folder)
        context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
        context.load_cert_chain(folder / 'server.pem', folder / 'server.key')
        context.load_verify_locations(folder / 'ca.pem')
        context.verify_mode = ssl.CERT_REQUIRED
        server = ThreadingHTTPServer(('127.0.0.1', 0), Reply)
        server.socket = context.wrap_socket(server.socket, server_side=True)
        with service(server) as port:
            client = binary('19-auth-and-mtls')
            run(client, f'https://localhost:{port}/', folder / 'ca.pem', folder / 'client.pem', folder / 'client.key')
            passed('mTLS trusted client')
            run(client, f'https://localhost:{port}/', folder / 'ca.pem', folder / 'bad.pem', folder / 'bad.key', success=False)
            passed('mTLS untrusted client rejected')
            run(client, f'https://127.0.0.1:{port}/', folder / 'ca.pem', folder / 'client.pem', folder / 'client.key', success=False)
            passed('TLS hostname mismatch rejected')
            run(client, f'https://localhost:{port}/', folder / 'bad.pem', folder / 'client.pem', folder / 'client.key', success=False)
            passed('TLS untrusted server CA rejected')
            missing = ssl.create_default_context(cafile=str(folder / 'ca.pem'))
            rejected = False
            try:
                with socket.create_connection(('127.0.0.1', port), timeout=3) as connection:
                    with missing.wrap_socket(connection, server_hostname='localhost') as connection:
                        connection.sendall(b'GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n')
                        rejected = not connection.recv(1024).startswith(b'HTTP/1.1 200')
            except (ssl.SSLError, OSError):
                rejected = True
            assert rejected, 'server accepted a client without a certificate'
            passed('mTLS missing client certificate rejected')
    process = subprocess.Popen([str(binary('19-auth-and-mtls', 'main2')), '0'], cwd=ROOT,
                               stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    lines = queue.Queue()
    reader = threading.Thread(target=lambda: lines.put(process.stdout.readline()), daemon=True)
    reader.start()
    try:
        line = lines.get(timeout=5)
        port = int(line.strip().rsplit(':', 1)[1])
        for method, token, expected in (('GET', '', 401), ('PUT', 'demo-reader', 403),
                                         ('GET', 'demo-reader', 200), ('PUT', 'demo-writer', 200)):
            with socket.create_connection(('127.0.0.1', port), timeout=3) as connection:
                request = f'{method} / HTTP/1.1\r\nHost: localhost\r\nContent-Length: 0\r\n'
                if token:
                    request += 'Authorization: Bearer ' + token + '\r\n'
                connection.sendall((request + '\r\n').encode())
                response = b''
                while True:
                    chunk = connection.recv(4096)
                    if not chunk:
                        break
                    response += chunk
                assert int(response.split(b' ')[1]) == expected, response
        output, error = process.communicate(timeout=5)
        assert process.returncode == 0, (output, error)
        passed('HTTP 401 / 403 / reader / writer')
    finally:
        if process.poll() is None:
            process.kill()
            process.communicate()
        reader.join(1)
    with service(ThreadingHTTPServer(('127.0.0.1', 0), Reply)) as port:
        run(binary('21-http-multiplexing'), f'http://127.0.0.1:{port}/a', f'http://127.0.0.1:{port}/b')
        passed('curl multi: two local HTTP/1.1 transfers')
    with socket.socket() as listener:
        listener.bind(('127.0.0.1', 0))
        listener.listen(1)
        listener.settimeout(5)
        errors = []
        def mqtt_fixture():
            try:
                with listener.accept()[0] as connection:
                    connection.settimeout(5)
                    header, body = packet(connection)
                    assert header == 0x10 and body.startswith(b'\x00\x04MQTT\x04')
                    connection.sendall(b'\x20\x02\x00\x00')
                    header, body = packet(connection)
                    assert header == 0x32
                    length = struct.unpack('!H', body[:2])[0]
                    assert body[2:2+length] == b'lesson/qos1'
                    assert body[2+length:4+length] == b'\x00\x07'
                    assert body[4+length:] == b'operation=order-42'
                    connection.sendall(b'\x40\x02\x00\x07')
                    assert packet(connection) == (0xe0, b'')
            except Exception as error:
                errors.append(repr(error))
        worker = threading.Thread(target=mqtt_fixture)
        worker.start()
        try:
            run(binary('29-mqtt-delivery', 'main2'), listener.getsockname()[1])
        finally:
            worker.join(7)
        assert not worker.is_alive() and not errors, errors
        passed('MQTT QoS 1 PUBLISH / PUBACK / DISCONNECT fixture')
    (REPORT / 'report.json').write_text(json.dumps({'passed': RESULTS}, ensure_ascii=False, indent=2) + '\n')


if __name__ == '__main__':
    main()
