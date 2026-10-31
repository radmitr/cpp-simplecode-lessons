"""Local integration checks for the C++ networking lessons (Windows/Linux).

Run from the repository root after building all lesson sources:
    python bonus/networking/tests/smoke.py
Requires Python 3 and openssl for the TLS checks. Never contacts external hosts.
"""

import argparse
import http.client
import http.server
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
BIN = ROOT / "build" / "bonus" / "networking"
SUFFIX = ".exe" if os.name == "nt" else ""


def executable(lesson, name):
    path = BIN / lesson / (name + SUFFIX)
    if not path.is_file():
        raise RuntimeError("Build the source first: " + str(path))
    return str(path)


def run(lesson, name, *args, success=True):
    result = subprocess.run(
        [executable(lesson, name), *map(str, args)],
        capture_output=True, text=True, timeout=10,
    )
    if (result.returncode == 0) != success:
        raise AssertionError((lesson, name, result.returncode, result.stdout, result.stderr))
    return result


class Server:
    def __init__(self, lesson, expected=0):
        self.lesson = lesson
        self.expected = expected
        self.lines = []
        self.messages = queue.Queue()
        self.process = None
        self.reader = None

    def __enter__(self):
        self.process = subprocess.Popen(
            [executable(self.lesson, "server"), "0"],
            stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
            stdin=subprocess.DEVNULL, text=True, bufsize=1,
        )

        def collect():
            for line in self.process.stdout:
                self.lines.append(line)
                self.messages.put(line)
            self.messages.put(None)

        self.reader = threading.Thread(target=collect, daemon=True)
        self.reader.start()
        try:
            line = self.messages.get(timeout=5)
            if line is None or not line.startswith("Listening on 127.0.0.1:"):
                raise AssertionError((self.lesson, line))
            self.port = int(line.rsplit(":", 1)[1])
            return self
        except BaseException:
            self.process.kill()
            self.process.wait(timeout=5)
            self.reader.join(timeout=5)
            self.process.stdout.close()
            raise

    def __exit__(self, kind, error, traceback):
        try:
            if kind:
                self.process.kill()
            code = self.process.wait(timeout=6)
            self.reader.join(timeout=5)
            if not kind and code != self.expected:
                raise AssertionError((self.lesson, code, "".join(self.lines)))
        finally:
            if self.process.poll() is None:
                self.process.kill()
                self.process.wait(timeout=5)
            self.reader.join(timeout=5)
            self.process.stdout.close()


def pair(lesson, expected, path=None):
    with Server(lesson) as server:
        target = server.port if path is None else "http://127.0.0.1:" + str(server.port) + path
        result = run(lesson, "client", target)
        assert expected in result.stdout, result.stdout
    print("PASS:", lesson, flush=True)


def tls_checks():
    openssl = shutil.which("openssl")
    if not openssl:
        raise RuntimeError("openssl was not found; install it or explicitly use --skip-tls")
    with tempfile.TemporaryDirectory(prefix="cpp-networking-tls-") as temporary:
        cert = Path(temporary) / "certificate.pem"
        key = Path(temporary) / "key.pem"
        subprocess.run(
            [openssl, "req", "-x509", "-newkey", "rsa:2048", "-nodes", "-days", "1",
             "-subj", "/CN=localhost", "-addext", "subjectAltName=DNS:localhost",
             "-keyout", str(key), "-out", str(cert)],
            capture_output=True, check=True, timeout=20,
        )

        class Handler(http.server.BaseHTTPRequestHandler):
            def handle(self):
                try:
                    super().handle()
                except (ConnectionResetError, BrokenPipeError):
                    pass  # Отрицательная проверка TLS может закрыть соединение до HTTP.

            def do_GET(self):
                body = b'{"tls":true}'
                self.send_response(200)
                self.send_header("Content-Length", str(len(body)))
                self.end_headers()
                self.wfile.write(body)

            def log_message(self, *args):
                pass

        with http.server.ThreadingHTTPServer(("127.0.0.1", 0), Handler) as server:
            context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
            context.load_cert_chain(str(cert), str(key))
            server.socket = context.wrap_socket(server.socket, server_side=True)
            worker = threading.Thread(target=server.serve_forever, daemon=True)
            worker.start()
            try:
                port = server.server_port
                url = "https://localhost:" + str(port) + "/"
                good = run("lesson-11-https", "main", url, cert)
                assert "HTTPS status: 200" in good.stdout, good.stdout
                # Без доверенного CA сертификат должен быть отвергнут.
                run("lesson-11-https", "main", url, success=False)
                # Даже с доверенным CA имя 127.0.0.1 не совпадает с DNS:localhost.
                run("lesson-11-https", "main", "https://127.0.0.1:" + str(port) + "/",
                    cert, success=False)
            finally:
                server.shutdown()
                worker.join(timeout=5)
    print("PASS: lesson-11-https (trusted CA, untrusted CA, hostname mismatch)", flush=True)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--skip-tls", action="store_true",
                        help="explicitly skip HTTPS checks when openssl is unavailable")
    args = parser.parse_args()

    addresses = run("lesson-01-addresses", "main")
    assert "IPv4:" in addresses.stdout or "IPv6:" in addresses.stdout
    assert "Port 80 -> network byte order -> 80" in addresses.stdout
    print("PASS: lesson-01-addresses", flush=True)
    pair("lesson-02-tcp-echo", "Echo: Hello over TCP")
    pair("lesson-03-tcp-framing", "Verified frame: 3 bytes")
    pair("lesson-04-udp-echo", "Datagram echo: Hello over UDP")
    pair("lesson-05-timeouts", "Expected timeout:")
    pair("lesson-06-http-get", "HTTP status: 200", "/hello")
    pair("lesson-07-http-post-json", '{"accepted":true,"value":42}', "/config")
    pair("lesson-08-rest-api", "DELETE /items/1 -> 204", "")
    pair("lesson-09-multi-client", "Verified: client 3")
    pair("lesson-10-background-sender", "Sender finished;")

    with Server("lesson-04-udp-echo") as server:
        with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as client:
            client.settimeout(3)
            client.sendto(b"", ("127.0.0.1", server.port))
            assert client.recvfrom(1024)[0] == b""
    print("PASS: empty UDP datagram is not TCP EOF", flush=True)

    with Server("lesson-03-tcp-framing", expected=1) as server:
        with socket.create_connection(("127.0.0.1", server.port), timeout=3) as client:
            client.sendall(struct.pack("!I", 65537))
    assert "frame is too large" in "".join(server.lines)
    print("PASS: oversized TCP frame rejected", flush=True)

    with socket.socket() as not_listening:
        not_listening.bind(("127.0.0.1", 0))
        result = run("lesson-02-tcp-echo", "client",
                     not_listening.getsockname()[1], success=False)
        assert "connect" in result.stderr or "deadline expired" in result.stderr, result.stderr
    print("PASS: unavailable port reported (refusal or connection timeout)", flush=True)

    with Server("lesson-06-http-get") as server:
        connection = http.client.HTTPConnection("127.0.0.1", server.port, timeout=3)
        try:
            connection.request("GET", "/missing")
            response = connection.getresponse()
            assert response.status == 404
            response.read()
        finally:
            connection.close()
    print("PASS: HTTP 404", flush=True)

    with Server("lesson-07-http-post-json") as server:
        connection = http.client.HTTPConnection("127.0.0.1", server.port, timeout=3)
        try:
            connection.request("POST", "/config", '{"value":01}',
                               {"Content-Type": "application/json"})
            response = connection.getresponse()
            assert response.status == 400
            response.read()
        finally:
            connection.close()
    print("PASS: malformed JSON rejected", flush=True)

    if args.skip_tls:
        print("SKIP: HTTPS checks (--skip-tls)", flush=True)
    else:
        tls_checks()
    print("All requested local networking checks passed.", flush=True)


if __name__ == "__main__":
    main()
