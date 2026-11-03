"""Loopback checks for lessons 20-23. Install tests/requirements.txt first.

--skip-services explicitly omits MQTT and successful HTTP/2 + HTTP/3 transfers.
WSS, strand and HTTPS fallback checks still run.
"""

import argparse
from contextlib import contextmanager
from pathlib import Path
import queue
import shutil
import socket
import subprocess
import sys
import tempfile
import threading
import time

sys.dont_write_bytecode = True
from smoke import BIN, Server, executable, run


class Captured:
    def __init__(self, command):
        self.command = list(map(str, command))
        self.lines = []
        self.messages = queue.Queue()

    def __enter__(self):
        self.process = subprocess.Popen(self.command, stdin=subprocess.DEVNULL,
                                        stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                                        text=True, encoding="utf-8", errors="backslashreplace")

        def collect():
            for line in self.process.stdout:
                self.lines.append(line)
                self.messages.put(line)
            self.messages.put(None)

        self.reader = threading.Thread(target=collect, daemon=True)
        self.reader.start()
        return self

    def expect(self, text):
        end = time.monotonic() + 10
        while True:
            try:
                line = self.messages.get(timeout=max(0, end - time.monotonic()))
            except queue.Empty:
                raise AssertionError(("missing", text, "".join(self.lines))) from None
            if line is None:
                raise AssertionError(("early exit", text, "".join(self.lines)))
            if text in line:
                return line.strip()

    def wait(self):
        code = self.process.wait(timeout=7)
        self.reader.join(timeout=5)
        assert code == 0, (code, "".join(self.lines))

    def __exit__(self, *error):
        if self.process.poll() is None:
            self.process.kill()
            self.process.wait(timeout=5)
        self.reader.join(timeout=5)
        self.process.stdout.close()


@contextmanager
def service(mode, cert=None, key=None):
    command = [sys.executable, "-B", Path(__file__).with_name("local_services.py"), mode]
    if cert:
        command += ["--cert", cert, "--key", key]
    with Captured(command) as process:
        port = int(process.expect("Listening on 127.0.0.1:").rsplit(":", 1)[1])
        yield port


def certificate(directory):
    openssl = shutil.which("openssl")
    if not openssl:
        raise RuntimeError("Install openssl and put it in PATH")
    cert, key = directory / "cert.pem", directory / "key.pem"
    subprocess.run([openssl, "req", "-x509", "-newkey", "rsa:2048", "-nodes", "-days", "1",
                    "-subj", "/CN=localhost", "-addext", "subjectAltName=DNS:localhost",
                    "-keyout", str(key), "-out", str(cert)],
                   capture_output=True, check=True, timeout=20)
    return cert, key


def wss_checks(cert, key):
    lesson = "lesson-20-wss"
    with Server(lesson, args=(cert, key)) as server:
        good = run(lesson, "client", server.port, cert)
        assert "WSS complete: 3 events" in good.stdout
    for ca, hostname in [("-", "localhost"), (cert, "127.0.0.1")]:
        with Server(lesson, expected=1, args=(cert, key)) as server:
            bad = run(lesson, "client", server.port, ca, hostname, success=False)
            assert "certificate verify failed" in bad.stderr.lower(), bad.stderr
    with Server(lesson, expected=1, args=(cert, key)) as server:
        with socket.create_connection(("127.0.0.1", server.port), timeout=3):
            server.process.wait(timeout=7)
    print("PASS: WSS, CA trust, hostname verification, clean TLS close and stalled handshake", flush=True)


def strand_checks():
    lesson = "lesson-21-asio-strand"
    with Server(lesson) as server:
        good = run(lesson, "client", server.port)
        assert "9 ordered replies" in good.stdout
    assert "Strand clients: 3; run threads: 3" in "".join(server.lines)
    with Server(lesson, expected=1) as server:
        connections = [socket.create_connection(("127.0.0.1", server.port), timeout=3) for _ in range(3)]
        try:
            server.process.wait(timeout=5)
        finally:
            for connection in connections:
                connection.close()
    print("PASS: strand, 3 run threads, ordered per-session replies and concurrent timeouts", flush=True)


def mqtt_checks():
    lesson = "lesson-22-mqtt"
    with service("mqtt") as port:
        with Captured([executable(lesson, "subscriber"), port]) as subscriber:
            subscriber.expect("Subscribed: lesson/temperature")
            result = run(lesson, "publisher", port)
            assert "Published QoS 0:" in result.stdout
            subscriber.wait()
            assert "Received: 23.5" in "".join(subscriber.lines)
    print("PASS: MQTT 3.1.1 with aMQTT broker, SUBACK readiness and QoS 0 routing", flush=True)


def http_checks(cert, key, skip_services):
    lesson = "lesson-23-http-versions"
    features = run(lesson, "main", "--features").stdout
    with service("h1", cert, key) as port:
        url = "https://localhost:" + str(port) + "/"
        for mode in ["h1"] + (["h2"] if "HTTP2=1" in features else []) + (["h3"] if "HTTP3=1" in features else []):
            response = run(lesson, "main", mode, url, cert)
            assert "Negotiated HTTP/1.1; status 200" in response.stdout
        if "HTTP2=1" in features:
            run(lesson, "main", "h2-only", url, cert, success=False)
        run(lesson, "main", "h1", url, success=False)
    if not skip_services:
        for mode, flag, expected in [("h2", "HTTP2=1", "2"), ("h3", "HTTP3=1", "3")]:
            if flag not in features:
                raise RuntimeError("Full checks require libcurl with " + flag + "; use --skip-services explicitly")
            with service(mode, cert, key) as port:
                response = run(lesson, "main", mode + "-only", "https://localhost:" + str(port) + "/", cert)
                assert "Negotiated HTTP/" + expected + "; status 200" in response.stdout
    print("PASS: HTTP versions, HTTPS fallback, strict mode and certificate rejection", flush=True)


def main(skip_services=False):
    with tempfile.TemporaryDirectory(prefix="advanced-", dir=BIN) as temporary:
        cert, key = certificate(Path(temporary))
        wss_checks(cert, key)
        strand_checks()
        if not skip_services:
            mqtt_checks()
        else:
            print("SKIP: MQTT broker and successful HTTP/2 + HTTP/3 (--skip-services)", flush=True)
        http_checks(cert, key, skip_services)
    print("All advanced networking checks passed.", flush=True)


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--skip-services", action="store_true")
    main(parser.parse_args().skip_services)
