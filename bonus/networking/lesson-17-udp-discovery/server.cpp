#include "discovery.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        const auto options = discovery::options(argc, argv, true);
        auto socket = net::makeSocket(SOCK_DGRAM);
        auto address = net::loopback(options.port);
        if (options.mode != "unicast") address.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(socket.get(), reinterpret_cast<const sockaddr*>(&address), sizeof(address)) != 0)
            net::fail("bind discovery");
        if (options.mode == "multicast")
        {
            ip_mreq membership{};
            inet_pton(AF_INET, discovery::group, &membership.imr_multiaddr);
            membership.imr_interface = options.interface;
            discovery::setOption(socket, IP_ADD_MEMBERSHIP, &membership, sizeof(membership));
            discovery::setOption(socket, IP_MULTICAST_IF, &options.interface, sizeof(options.interface));
        }
        std::cout << "Listening on " << (options.mode == "unicast" ? "127.0.0.1:" : "0.0.0.0:")
                  << net::localPort(socket) << std::endl;
        int replies = 0;
        for (int packet = 0; packet < 3; ++packet)
        {
            try
            {
                net::waitReady(socket, false, net::after(packet == 0
                    ? std::chrono::milliseconds(15000) : std::chrono::milliseconds(750)));
            }
            catch (const net::Timeout&)
            {
                if (packet == 0) throw;
                break;
            }
            char bytes[512]{};
            sockaddr_in sender{};
            net::AddressLength length = sizeof(sender);
            const auto size = recvfrom(socket.get(), bytes, sizeof(bytes), 0,
                                       reinterpret_cast<sockaddr*>(&sender), &length);
            if (size < 0) net::fail("recvfrom discovery");
            std::istringstream input(std::string(bytes, static_cast<std::size_t>(size)));
            std::string command, nonce, extra;
            if (!(input >> command >> nonce) || input >> extra || command != "DISCOVER" || nonce.size() > 64)
                continue;
            const std::string reply = "DEVICE demo-device " + nonce;
            const auto sent = sendto(socket.get(), reply.data(), static_cast<int>(reply.size()), 0,
                                     reinterpret_cast<const sockaddr*>(&sender), length);
            if (sent != static_cast<int>(reply.size())) net::fail("sendto discovery");
            ++replies;
        }
        std::cout << "Discovery replies: " << replies << '\n';
        return replies > 0 ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
