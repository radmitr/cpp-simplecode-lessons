#ifndef NETWORKING_RESOLVED_ADDRESS_HPP
#define NETWORKING_RESOLVED_ADDRESS_HPP

#include "net.hpp"
#include <memory>

namespace net
{
inline Socket connectHost(const std::string& hostname, std::uint16_t port, Deadline deadline)
{
    addrinfo hints{};
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    addrinfo* raw = nullptr;
    const auto service = std::to_string(port);
    const int error = getaddrinfo(hostname.c_str(), service.c_str(), &hints, &raw);
    if (error != 0) throw std::runtime_error("getaddrinfo failed: " + std::to_string(error));
    std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> addresses(raw, freeaddrinfo);
    std::string lastFailure = "no IPv4/IPv6 addresses";
    for (const addrinfo* entry = addresses.get(); entry; entry = entry->ai_next)
    {
        if (entry->ai_family != AF_INET && entry->ai_family != AF_INET6) continue;
        if (Clock::now() >= deadline) throw Timeout();
        try
        {
            return connectAddress(entry->ai_addr, static_cast<AddressLength>(entry->ai_addrlen), deadline);
        }
        catch (const std::exception& failure)
        {
            lastFailure = failure.what();
        }
    }
    throw std::runtime_error("all resolved addresses failed: " + lastFailure);
}
} // namespace net
#endif
