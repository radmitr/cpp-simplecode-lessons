"""Local integration checks for lessons 12-19. Build the sources first.

python bonus/networking/tests/smoke_extended.py [--multicast]
The optional multicast check explicitly uses the loopback interface.
No LAN broadcast packets or external connections are sent by this script.
"""

import argparse
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
import socket
import struct
import sys
import tempfile
import zlib

sys.dont_write_bytecode = True
from smoke import BIN, Server, run


def pair(lesson, expected, *, server_args=(), client_args=()):
    with Server(lesson, args=server_args) as server:
        result = run(lesson, "client", server.port, *client_args)
        assert expected in result.stdout, result.stdout
    print("PASS:", lesson, flush=True)
    return server


def unused_port():
    with socket.socket() as reservation:
        reservation.bind(("127.0.0.1", 0))
        return reservation.getsockname()[1]


def send_frame(connection, body):
    connection.sendall(struct.pack("!I", len(body)) + body)


def transfer_checks():
    lesson = "lesson-16-file-transfer"
    with tempfile.TemporaryDirectory(prefix="transfer-test-", dir=BIN) as temporary:
        root = Path(temporary)
        target = root / "default"
        pair(lesson, "File confirmed: 131072 bytes", server_args=(target,))
        received = list(target.glob("*/payload.bin"))
        assert len(received) == 1
        assert received[0].read_bytes() == bytes(range(256)) * 512
        # Предыдущий файл остаётся на месте, вторая передача создаёт другой каталог.
        pair(lesson, "File confirmed: 131072 bytes", server_args=(target,))
        assert len(list(target.glob("*/payload.bin"))) == 2

        for name, content in [("empty.bin", b""), ("known-crc.bin", b"123456789")]:
            source = root / name
            source.write_bytes(content)
            output = root / (name + "-received")
            pair(lesson, "CRC32 " + str(zlib.crc32(content)),
                 server_args=(output,), client_args=(source,))
            assert next(output.glob("*/payload.bin")).read_bytes() == content

        for name, metadata, payload, error in [
            (b"test.bin", struct.pack("!II", 1, 0), b"B", "CRC32 mismatch"),
            (b"../escape", b"", b"", "invalid file name"),
            (b"test.bin", struct.pack("!II", 1048577, 0), b"", "1 MiB"),
        ]:
            output = root / "rejected"
            with Server(lesson, expected=1, args=(output,)) as server:
                with socket.create_connection(("127.0.0.1", server.port), timeout=3) as client:
                    send_frame(client, name)
                    if metadata:
                        client.sendall(metadata + payload)
                    server.process.wait(timeout=5)
            assert error in "".join(server.lines), server.lines
            assert not list(output.glob("*/payload.*"))
    print("PASS: file bytes, CRC32, empty file, unique directories and rejected transfers", flush=True)


def discovery_nonce_check():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as receiver:
        receiver.bind(("127.0.0.1", 0))
        receiver.settimeout(5)

        def respond():
            for _ in range(3):
                data, address = receiver.recvfrom(512)
                nonce = data.split()[1]
                receiver.sendto(b"DEVICE wrong invalid-nonce", address)
                receiver.sendto(b"DEVICE good " + nonce, address)

        with ThreadPoolExecutor(max_workers=1) as executor:
            task = executor.submit(respond)
            result = run("lesson-17-udp-discovery", "client", receiver.getsockname()[1])
            task.result(timeout=5)
        assert "Found good" in result.stdout and "Found wrong" not in result.stdout
        assert "Discovered devices: 1" in result.stdout
    print("PASS: discovery correlation and duplicate filtering", flush=True)


def websocket_interop():
    # Независимый минимальный клиент проверяет handshake и framing сервера Beast.
    with Server("lesson-19-websocket") as server:
        with socket.create_connection(("127.0.0.1", server.port), timeout=3) as connection:
            connection.settimeout(3)
            request = (
                "GET /events HTTP/1.1\r\n"
                "Host: localhost\r\nUpgrade: websocket\r\nConnection: Upgrade\r\n"
                "Sec-WebSocket-Key: dGhlIHNhbXBsZSBub25jZQ==\r\n"
                "Sec-WebSocket-Version: 13\r\n\r\n"
            )
            connection.sendall(request.encode("ascii"))
            pending = bytearray()

            def take(count):
                while len(pending) < count:
                    block = connection.recv(4096)
                    assert block, "unexpected WebSocket EOF"
                    pending.extend(block)
                result = bytes(pending[:count])
                del pending[:count]
                return result

            header = bytearray()
            while not header.endswith(b"\r\n\r\n"):
                header += take(1)
            assert header.startswith(b"HTTP/1.1 101")
            assert b"Sec-WebSocket-Accept: s3pPLMBiTxaQ9kYGzzhZRbK+xOo=" in header

            def read_frame():
                flags, length = take(2)
                assert not length & 128, "server frames must not be masked"
                assert length < 126, "test expects small frames"
                return flags, take(length)

            def masked_frame(opcode, payload):
                mask = b"abcd"
                encoded = bytes(value ^ mask[i % 4] for i, value in enumerate(payload))
                connection.sendall(bytes([0x80 | opcode, 0x80 | len(payload)]) + mask + encoded)

            for number in range(1, 4):
                opcode, payload = read_frame()
                assert opcode == 0x81 and payload == ("tick " + str(number)).encode("ascii")
            masked_frame(1, b"ACK 3")
            opcode, payload = read_frame()
            assert opcode == 0x88 and payload[:2] == struct.pack("!H", 1000)
            masked_frame(8, payload)
    print("PASS: independent WebSocket handshake, text frames, masking and close", flush=True)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--multicast", action="store_true",
                        help="also check multicast through 127.0.0.1")
    args = parser.parse_args()
    pair("lesson-12-ipv6", "IPv6 echo: Hello over IPv6")
    pair("lesson-12-ipv6", "IPv6 echo: Hello over IPv6", client_args=("::1",))

    port = unused_port()
    with Server("lesson-13-reconnect", port=port, wait_ready=False):
        result = run("lesson-13-reconnect", "client", port)
        assert "Connected after retry" in result.stdout
    with socket.socket() as reservation:
        reservation.bind(("127.0.0.1", 0))
        port = reservation.getsockname()[1]
        exhausted = run("lesson-13-reconnect", "client", port, success=False)
        assert "Attempt 6" in exhausted.stdout
        cancelled = run("lesson-13-reconnect", "client", port, "--cancel")
        assert "Retry cancelled" in cancelled.stdout
    print("PASS: reconnect success, bounded exhaustion and cancellation", flush=True)

    pair("lesson-14-heartbeat", "Heartbeat timeout:")
    ack = pair("lesson-15-request-ack", "ERROR req-1 conflict")
    assert "Applications: 1" in "".join(ack.lines) and "Total: 5" in "".join(ack.lines)
    transfer_checks()
    pair("lesson-17-udp-discovery", "Discovered devices: 1")
    discovery_nonce_check()
    if args.multicast:
        pair("lesson-17-udp-discovery", "Discovered devices: 1",
             server_args=("multicast", "127.0.0.1"), client_args=("multicast", "127.0.0.1"))
    else:
        print("SKIP: optional loopback multicast (--multicast)", flush=True)

    pair("lesson-18-asio", "Async echo verified: 3 clients")
    with Server("lesson-18-asio", expected=1) as server:
        connections = [socket.create_connection(("127.0.0.1", server.port), timeout=3) for _ in range(3)]
        try:
            server.process.wait(timeout=5)  # Ничего не посылаем: три таймера завершат сессии.
        finally:
            for connection in connections:
                connection.close()
    assert "".join(server.lines).count("Session:") == 3
    print("PASS: asynchronous session read timeouts", flush=True)
    pair("lesson-19-websocket", "WebSocket complete: 3 events")
    websocket_interop()
    with Server("lesson-19-websocket", expected=1) as server:
        with socket.create_connection(("127.0.0.1", server.port), timeout=3):
            server.process.wait(timeout=4)  # Нет HTTP Upgrade: истечёт handshake timeout.
    print("PASS: WebSocket handshake timeout", flush=True)
    print("All extended networking checks passed.", flush=True)


if __name__ == "__main__":
    main()
