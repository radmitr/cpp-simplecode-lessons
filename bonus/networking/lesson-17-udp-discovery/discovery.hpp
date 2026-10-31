#ifndef NETWORKING_DISCOVERY_HPP
#define NETWORKING_DISCOVERY_HPP

#include "../common/net.hpp"
#include <sstream>

namespace discovery
{
inline constexpr const char* group = "239.255.42.99";
struct Options
{
    std::uint16_t port;
    std::string mode;
    in_addr interface;
};

inline Options options(int argc, char* argv[], bool server)
{
    if (argc > 4) throw std::runtime_error("Usage: program [port] [unicast|broadcast|multicast] [interface-ip]");
    Options result{
        argc >= 2 ? net::parsePort(argv[1], server) : std::uint16_t{42017},
        argc >= 3 ? argv[2] : "unicast", {}
    };
    if (result.mode != "unicast" && result.mode != "broadcast" && result.mode != "multicast")
        throw std::runtime_error("unknown discovery mode");
    const char* interface = argc == 4 ? argv[3] : "0.0.0.0";
    if (inet_pton(AF_INET, interface, &result.interface) != 1)
        throw std::runtime_error("invalid interface IPv4 address");
    return result;
}

inline void setOption(const net::Socket& socket, int name, const void* value, int size, int level = IPPROTO_IP)
{
    if (setsockopt(socket.get(), level, name, static_cast<const char*>(value), size) != 0)
        net::fail("setsockopt discovery");
}

inline std::string endpoint(const sockaddr_in& address)
{
    char text[INET_ADDRSTRLEN]{};
    if (!inet_ntop(AF_INET, &address.sin_addr, text, sizeof(text))) net::fail("inet_ntop");
    return std::string(text) + ':' + std::to_string(ntohs(address.sin_port));
}
} // namespace discovery
#endif
