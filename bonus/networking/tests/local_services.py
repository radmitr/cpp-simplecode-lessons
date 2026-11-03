"""Finite loopback MQTT / HTTPS test services. See tests/README.md.

These services are fixtures, not general-purpose server implementations.
"""

import argparse
import asyncio
import logging
import ssl
import sys

sys.dont_write_bytecode = True


async def mqtt_service(port):
    from amqtt.broker import Broker

    broker = Broker({
        "listeners": {"default": {"type": "tcp", "bind": "127.0.0.1:" + str(port)}},
        "plugins": {"amqtt.plugins.authentication.AnonymousAuthPlugin": {"allow_anonymous": True}},
    })
    await broker.start()
    # aMQTT не предоставляет публичного метода получения порта при bind(..., 0).
    # Это единственное обращение к внутренностям; версия закреплена в requirements.
    actual = broker._servers["default"].instance.sockets[0].getsockname()[1]
    return actual, broker.shutdown


async def https_service(mode, port, cert, key):
    context = ssl.SSLContext(ssl.PROTOCOL_TLS_SERVER)
    context.load_cert_chain(cert, key)
    context.set_alpn_protocols(["h2" if mode == "h2" else "http/1.1"])

    async def handle(reader, writer):
        try:
            if mode == "h1":
                await asyncio.wait_for(reader.readuntil(b"\r\n\r\n"), 5)
                writer.write(b"HTTP/1.1 200 OK\r\nContent-Length: 2\r\nConnection: close\r\n\r\nok")
                await writer.drain()
            else:
                import h2.config
                import h2.connection
                import h2.events

                protocol = h2.connection.H2Connection(h2.config.H2Configuration(client_side=False))
                protocol.initiate_connection()
                writer.write(protocol.data_to_send())
                await writer.drain()
                while True:
                    block = await asyncio.wait_for(reader.read(65536), 5)
                    if not block:
                        break
                    done = False
                    for event in protocol.receive_data(block):
                        if isinstance(event, h2.events.StreamEnded):
                            protocol.send_headers(event.stream_id, [(":status", "200"), ("content-length", "2")])
                            protocol.send_data(event.stream_id, b"ok", end_stream=True)
                            done = True
                    writer.write(protocol.data_to_send())
                    await writer.drain()
                    if done:
                        break
        except (ConnectionError, asyncio.TimeoutError, asyncio.IncompleteReadError):
            pass  # Отрицательные проверки могут закрыть соединение до запроса.
        finally:
            writer.close()
            try:
                await writer.wait_closed()
            except (ConnectionError, ssl.SSLError):
                pass

    server = await asyncio.start_server(handle, "127.0.0.1", port, ssl=context)

    async def close():
        server.close()
        await server.wait_closed()

    return server.sockets[0].getsockname()[1], close


async def http3_service(port, cert, key):
    from aioquic.asyncio import QuicConnectionProtocol, serve
    from aioquic.h3.connection import H3_ALPN, H3Connection
    from aioquic.h3.events import HeadersReceived
    from aioquic.quic.configuration import QuicConfiguration
    from aioquic.quic.events import ProtocolNegotiated

    class Http3(QuicConnectionProtocol):
        http = None

        def quic_event_received(self, event):
            if isinstance(event, ProtocolNegotiated):
                self.http = H3Connection(self._quic)
            if self.http:
                for message in self.http.handle_event(event):
                    if isinstance(message, HeadersReceived):
                        self.http.send_headers(message.stream_id, [(b":status", b"200"), (b"content-length", b"2")])
                        self.http.send_data(message.stream_id, b"ok", end_stream=True)
                self.transmit()

    config = QuicConfiguration(is_client=False, alpn_protocols=H3_ALPN)
    config.load_cert_chain(cert, key)
    server = await serve("127.0.0.1", port, configuration=config, create_protocol=Http3)
    actual = server._transport.get_extra_info("sockname")[1]

    async def close():
        server.close()

    return actual, close


async def main(args):
    if args.mode == "mqtt":
        port, close = await mqtt_service(args.port)
    else:
        if not args.cert or not args.key:
            raise ValueError("HTTPS needs --cert and --key")
        if args.mode == "h3":
            port, close = await http3_service(args.port, args.cert, args.key)
        else:
            port, close = await https_service(args.mode, args.port, args.cert, args.key)
    print("Listening on 127.0.0.1:" + str(port), flush=True)
    try:
        await asyncio.sleep(args.seconds)  # Время жизни службы, не синхронизация теста.
    finally:
        await close()


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("mode", choices=("mqtt", "h1", "h2", "h3"))
    parser.add_argument("--port", type=int, default=0)
    parser.add_argument("--cert")
    parser.add_argument("--key")
    parser.add_argument("--seconds", type=float, default=60)
    arguments = parser.parse_args()
    logging.basicConfig(level=logging.ERROR)
    try:
        asyncio.run(main(arguments))
    except KeyboardInterrupt:
        pass
