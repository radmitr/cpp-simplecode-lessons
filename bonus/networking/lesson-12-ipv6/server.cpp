#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::makeSocket(SOCK_STREAM, AF_INET6);
        const int onlyV6 = 1;
        if (setsockopt(listener.get(), IPPROTO_IPV6, IPV6_V6ONLY,
                       reinterpret_cast<const char*>(&onlyV6), sizeof(onlyV6)) != 0)
            net::fail("IPV6_V6ONLY");
        sockaddr_in6 address{};
        address.sin6_family = AF_INET6;
        address.sin6_port = htons(net::portArgument(argc, argv, 42012, true));
        if (inet_pton(AF_INET6, "::1", &address.sin6_addr) != 1) net::fail("inet_pton");
        if (bind(listener.get(), reinterpret_cast<const sockaddr*>(&address), sizeof(address)) != 0)
            net::fail("bind IPv6");
        if (listen(listener.get(), 4) != 0) net::fail("listen");
        std::cout << "Listening on [::1]:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        const auto message = net::receiveLine(client, net::after(std::chrono::seconds(3)));
        net::sendAll(client, message + '\n', net::after(std::chrono::seconds(3)));
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
