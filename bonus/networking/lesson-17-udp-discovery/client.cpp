#include "discovery.hpp"
#include <iostream>
#include <random>
#include <set>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        const auto options = discovery::options(argc, argv, false);
        auto socket = net::makeSocket(SOCK_DGRAM);
        sockaddr_in source{};
        source.sin_family = AF_INET;
        source.sin_addr = options.interface;
        if (bind(socket.get(), reinterpret_cast<const sockaddr*>(&source), sizeof(source)) != 0)
            net::fail("bind discovery client");
        auto destination = net::loopback(options.port);
        if (options.mode == "broadcast")
        {
            const int enabled = 1;
            discovery::setOption(socket, SO_BROADCAST, &enabled, sizeof(enabled), SOL_SOCKET);
            destination.sin_addr.s_addr = htonl(INADDR_BROADCAST);
        }
        if (options.mode == "multicast")
        {
            inet_pton(AF_INET, discovery::group, &destination.sin_addr);
            discovery::setOption(socket, IP_MULTICAST_IF, &options.interface, sizeof(options.interface));
            const int ttl = 1;
            discovery::setOption(socket, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
            const int loop = 1;
            discovery::setOption(socket, IP_MULTICAST_LOOP, &loop, sizeof(loop));
        }
        std::random_device random;
        const auto nonce = std::to_string(random()) + "-" + std::to_string(random());
        const auto request = "DISCOVER " + nonce;
        std::set<std::string> devices;
        for (int attempt = 0; attempt < 3; ++attempt)
        {
            const auto sent = sendto(socket.get(), request.data(), static_cast<int>(request.size()), 0,
                                     reinterpret_cast<const sockaddr*>(&destination), sizeof(destination));
            if (sent != static_cast<int>(request.size())) net::fail("sendto discover");
            const auto deadline = net::after(std::chrono::milliseconds(200));
            for (;;)
            {
                try { net::waitReady(socket, false, deadline); }
                catch (const net::Timeout&) { break; }
                char bytes[512]{};
                sockaddr_in sender{};
                net::AddressLength length = sizeof(sender);
                const auto size = recvfrom(socket.get(), bytes, sizeof(bytes), 0,
                                           reinterpret_cast<sockaddr*>(&sender), &length);
                if (size < 0) net::fail("recvfrom discovery");
                std::istringstream input(std::string(bytes, static_cast<std::size_t>(size)));
                std::string command, name, receivedNonce, extra;
                if (!(input >> command >> name >> receivedNonce) || input >> extra
                    || command != "DEVICE" || receivedNonce != nonce)
                    continue;
                const auto endpoint = discovery::endpoint(sender);
                if (devices.insert(endpoint).second)
                    std::cout << "Found " << name << " at " << endpoint << '\n';
            }
        }
        std::cout << "Discovered devices: " << devices.size() << '\n';
        return devices.empty() ? 1 : 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
