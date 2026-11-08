// C++17 — from_chars; сетевой механизм — IPv4 CIDR и longest-prefix match.
#include <array>
#include <charconv>
#include <cstdint>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <system_error>

#include "../../../basics/additions/common/check.hpp"

std::uint32_t address(std::string_view text)
{
    std::uint32_t value = 0;
    for (int index = 0; index < 4; ++index)
    {
        const auto end = text.find('.');
        const auto part = text.substr(0, end);
        unsigned octet = 0;
        const auto result = std::from_chars(part.data(), part.data() + part.size(), octet);
        if (part.empty() || result.ec != std::errc{} || result.ptr != part.data() + part.size()
            || octet > 255 || (index < 3) != (end != std::string_view::npos))
            throw std::invalid_argument("invalid IPv4 address");
        value = (value << 8) | octet;
        if (end != std::string_view::npos) text.remove_prefix(end + 1);
    }
    return value;
}
std::uint32_t mask(unsigned prefix)
{
    if (prefix > 32) throw std::invalid_argument("prefix must be 0..32");
    return prefix == 0 ? 0 : UINT32_MAX << (32 - prefix);
}
struct Route { std::uint32_t network; unsigned prefix; std::string_view next; };
std::string_view select(std::uint32_t target, const std::array<Route, 3>& routes)
{
    const Route* best = nullptr;
    for (const auto& route : routes)
        if ((target & mask(route.prefix)) == (route.network & mask(route.prefix))
            && (!best || route.prefix > best->prefix)) best = &route;
    if (!best) throw std::runtime_error("no route");
    return best->next;
}
int main()
{
    try
    {
        const auto host = address("192.168.10.42");
        check((host & mask(24)) == address("192.168.10.0"), "subnet");
        check(mask(0) == 0 && mask(32) == UINT32_MAX, "boundary prefixes without invalid shifts");
        const std::array routes{Route{0, 0, "gateway"}, Route{address("192.168.0.0"), 16, "lan"},
            Route{address("192.168.10.0"), 24, "lab"}};
        check(select(host, routes) == "lab" && select(address("8.8.8.8"), routes) == "gateway", "longest prefix");
        for (const auto bad : {"1.2.3", "256.0.0.1", "1.2.3.4.5", "1..3.4"})
        {
            bool rejected = false;
            try { address(bad); } catch (const std::invalid_argument&) { rejected = true; }
            check(rejected, "invalid address rejected");
        }
        std::cout << "192.168.10.0/24 -> lab; 8.8.8.8 -> gateway\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
