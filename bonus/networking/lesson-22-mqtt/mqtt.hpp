// C++17 — std::string_view; MQTT 3.1.1 — внешний сетевой протокол.
#ifndef NETWORKING_MQTT_HPP
#define NETWORKING_MQTT_HPP

#include "../common/net.hpp"
#include <iostream>

namespace mqtt
{
inline net::Deadline deadline() { return net::after(std::chrono::seconds(5)); }

inline std::string field(std::string_view text)
{
    if (text.size() > 1024) throw std::runtime_error("Поле MQTT длиннее 1024 байт");
    std::string result;
    result += static_cast<char>(text.size() >> 8);
    result += static_cast<char>(text.size() & 255);
    result.append(text);
    return result;
}

inline void send(const net::Socket& socket, unsigned char header, std::string_view body = {})
{
    if (body.size() > 4096) throw std::runtime_error("Пакет MQTT слишком большой");
    std::string packet(1, static_cast<char>(header));
    auto remaining = body.size();
    do
    {
        auto digit = static_cast<unsigned char>(remaining % 128);
        remaining /= 128;
        if (remaining) digit |= 128;
        packet += static_cast<char>(digit);
    } while (remaining);
    packet.append(body);
    net::sendAll(socket, packet, deadline());
}

struct Packet
{
    unsigned char header;
    std::string body;
};

inline Packet receive(const net::Socket& socket,
                      std::chrono::milliseconds timeout = std::chrono::seconds(5))
{
    const auto end = net::after(timeout); // Один дедлайн на заголовок и тело.
    const auto header = static_cast<unsigned char>(net::receiveExact(socket, 1, end)[0]);
    std::size_t length = 0;
    std::size_t multiplier = 1;
    for (int count = 0; count < 4; ++count)
    {
        const auto byte = static_cast<unsigned char>(net::receiveExact(socket, 1, end)[0]);
        length += (byte & 127) * multiplier;
        if (length > 4096) throw std::runtime_error("Пакет MQTT слишком большой");
        if (!(byte & 128)) return {header, net::receiveExact(socket, length, end)};
        multiplier *= 128;
    }
    throw std::runtime_error("Неверная Remaining Length");
}

inline net::Socket connect(std::uint16_t port, std::string_view id)
{
    auto socket = net::connectLoopback(port, deadline());
    std::string body = field("MQTT");
    // Уровень 4 = MQTT 3.1.1; Clean Session; Keep Alive = 0 (пример конечный).
    body.append("\x04\x02\x00\x00", 4);
    body += field(id);
    send(socket, 0x10, body);
    const auto response = receive(socket);
    if (response.header != 0x20 || response.body != std::string(2, '\0'))
        throw std::runtime_error("Брокер отклонил CONNECT или прислал неверный CONNACK");
    return socket;
}

inline constexpr std::string_view topic = "lesson/temperature";
} // namespace mqtt
#endif
