"""Integration checks for 24-chat; build server.cpp and client.cpp first.

python bonus/networking/tests/smoke_chat.py
Only loopback connections, no external services or scheduling sleeps.
"""

from contextlib import ExitStack
import queue
import socket
import subprocess
import sys
import threading
import time

sys.dont_write_bytecode = True
from smoke import executable

LESSON = "24-chat"


class Program:
    def __init__(self, name, *arguments):
        self.command = [executable(LESSON, name), *map(str, arguments)]
        self.lines = []
        self.messages = queue.Queue()

    def __enter__(self):
        self.process = subprocess.Popen(
            self.command, stdin=subprocess.PIPE, stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT, text=True, encoding="utf-8",
            errors="backslashreplace", bufsize=1,
        )

        def collect():
            for line in self.process.stdout:
                self.lines.append(line)
                self.messages.put(line)
            self.messages.put(None)

        self.reader = threading.Thread(target=collect, daemon=True)
        self.reader.start()
        return self

    def send(self, line):
        self.process.stdin.write(line + "\n")
        self.process.stdin.flush()

    def expect(self, text, timeout=6):
        deadline = time.monotonic() + timeout
        while True:
            try:
                line = self.messages.get(timeout=max(0, deadline - time.monotonic()))
            except queue.Empty:
                raise AssertionError(("missing", text, self.command, "".join(self.lines))) from None
            if line is None:
                raise AssertionError(("early exit", text, "".join(self.lines)))
            if text in line:
                return line.strip()

    def wait_exit(self):
        code = self.process.wait(timeout=5)
        self.reader.join(timeout=5)
        assert not self.reader.is_alive()
        assert code == 0, (self.command, code, "".join(self.lines))

    def stop(self):
        if self.process.poll() is None:
            self.send("/quit")
        self.wait_exit()

    def __exit__(self, kind, error, traceback):
        try:
            if not kind:
                self.stop()
        finally:
            if self.process.poll() is None:
                self.process.kill()
                self.process.wait(timeout=5)
            self.reader.join(timeout=5)
            self.process.stdin.close()
            self.process.stdout.close()


def listening(server):
    return int(server.expect("Listening on 127.0.0.1:").rsplit(":", 1)[1])


def connect(port):
    connection = socket.create_connection(("127.0.0.1", port), timeout=5)
    connection.settimeout(7)
    return connection


def assert_closed(connection):
    try:
        assert connection.recv(1) == b"", "expected EOF"
    except (ConnectionResetError, ConnectionAbortedError):
        pass  # Закрытие с непрочитанными данными может дать RST вместо EOF.


def assert_reader_closed(reader):
    try:
        assert reader.read(1) == b"", "unexpected data before EOF"
    except (ConnectionResetError, ConnectionAbortedError):
        pass


def chat_and_restart():
    with ExitStack() as resources:
        server = resources.enter_context(Program("server", 0))
        port = listening(server)
        alice = resources.enter_context(Program("client", port, "alice"))
        bob = resources.enter_context(Program("client", port, "bob"))
        alice.expect("Подключено: alice")
        bob.expect("Подключено: bob")
        alice.send("Привет, чат!")
        alice.expect("alice: Привет, чат!")
        bob.expect("alice: Привет, чат!")
        bob.send("first")
        bob.send("second")
        alice.expect("bob: first")
        alice.expect("bob: second")
        server.stop()
        alice.expect("Связь потеряна:")
        bob.expect("Связь потеряна:")
        with Program("server", port) as restarted:
            assert listening(restarted) == port
            alice.expect("Подключено: alice")
            bob.expect("Подключено: bob")
            alice.send("after restart")
            bob.expect("alice: after restart")
            # EOF консоли останавливает клиент так же, как /quit.
            bob.process.stdin.close()
            bob.wait_exit()
            alice.stop()
    print("PASS: UTF-8 broadcast, message order, server restart, reconnect and console EOF", flush=True)


def server_protocol():
    with Program("server", 0) as server:
        port = listening(server)
        with connect(port) as connection, connection.makefile("rb") as reader:
            connection.sendall(b"HELLO raw\n")
            assert reader.readline() == b"READY raw\n"
            # TCP может объединить эти записи или разделить любую из них.
            connection.sendall(b"MSG split ")
            connection.sendall(b"frame\nPING 1\n")
            assert reader.readline() == b"CHAT raw split frame\n"
            assert reader.readline() == b"PONG 1\n"
            connection.sendall(b"MSG " + b"x" * 1025 + b"\n")
            assert_closed(connection)
        for payload in (b"HELLO invalid name\n", b"x" * 5000):
            with connect(port) as connection:
                connection.sendall(payload)
                assert_closed(connection)
        for payload in (b"PING 0\n", b"MSG bad\x00text\n"):
            with connect(port) as connection, connection.makefile("rb") as reader:
                connection.sendall(b"HELLO raw\n")
                assert reader.readline() == b"READY raw\n"
                connection.sendall(payload)
                assert_reader_closed(reader)
        # Клиент без HELLO не удерживает серверный слот бесконечно.
        with connect(port) as silent:
            assert_closed(silent)
    print("PASS: independent framing, protocol errors, size bounds and idle timeout", flush=True)


def accept(listener):
    connection, _ = listener.accept()
    connection.settimeout(5)
    return connection


def listener_socket():
    listener = socket.socket()
    listener.bind(("127.0.0.1", 0))
    listener.listen()
    listener.settimeout(5)
    return listener


def heartbeat_recovery():
    with listener_socket() as listener, Program("client", listener.getsockname()[1], "alice") as client:
        with accept(listener) as first, first.makefile("rb") as reader:
            assert reader.readline() == b"HELLO alice\n"
            first.sendall(b"READY alice\n")
            client.expect("Подключено: alice")
            assert reader.readline() == b"PING 1\n"
            client.send("before-loss")
            assert reader.readline() == b"MSG before-loss\n"
            # CHAT не заменяет подтверждение конкретного PING. TCP остаётся открыт.
            first.sendall(b"CHAT bot unrelated traffic\n")
            client.expect("bot: unrelated traffic")
            client.expect("heartbeat: PONG не получен за 1500 мс")
            assert_reader_closed(reader)
        with accept(listener) as second, second.makefile("rb") as reader:
            assert reader.readline() == b"HELLO alice\n"
            second.sendall(b"READY alice\n")
            client.expect("Подключено: alice")
            assert reader.readline() == b"PING 1\n"
            second.sendall(b"PONG 1\n")
            client.send("after-loss")
            # Старое сообщение автоматически не повторяется в новом соединении.
            assert reader.readline() == b"MSG after-loss\n"
            second.sendall(b"CHAT alice after-loss\n")
            client.expect("alice: after-loss")
            assert reader.readline() == b"PING 2\n"
            client.stop()  # Выход во время ожидания PONG и незавершённого чтения.
            assert_reader_closed(reader)
    print("PASS: missing PONG, old socket closed, fresh session, no replay and cancellation", flush=True)


def client_failures():
    with socket.socket() as reservation:
        reservation.bind(("127.0.0.1", 0))
        with Program("client", reservation.getsockname()[1], "offline") as client:
            for pause in (100, 200, 400, 800, 1600, 2000):
                client.expect("Повтор через " + str(pause) + " мс.")
            client.send("not queued")
            client.expect("сообщение не отправлено и не сохранено")
            client.stop()  # Длинная пауза повтора отменяется без ожидания таймера.
    for mode in ("no-ready", "bad-pong"):
        with listener_socket() as listener, Program("client", listener.getsockname()[1], "check") as client:
            with accept(listener) as connection, connection.makefile("rb") as reader:
                assert reader.readline() == b"HELLO check\n"
                if mode == "no-ready":
                    client.expect("таймаут подключения или READY")
                else:
                    connection.sendall(b"READY check\n")
                    assert reader.readline() == b"PING 1\n"
                    connection.sendall(b"PONG 999\n")
                    client.expect("неверный номер PONG")
                assert_reader_closed(reader)
                client.stop()
    invalid = subprocess.run([executable(LESSON, "client"), "42024", "bad name"],
                             capture_output=True, timeout=5)
    assert invalid.returncode == 1
    print("PASS: capped backoff, offline input, retry cancellation, READY deadline and bad PONG", flush=True)


def main():
    chat_and_restart()
    server_protocol()
    heartbeat_recovery()
    client_failures()
    print("All chat checks passed.", flush=True)


if __name__ == "__main__":
    main()
