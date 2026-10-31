#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto socket = net::makeSocket(SOCK_DGRAM);
        const auto destination = net::loopback(net::portArgument(argc, argv, 42004));
        const std::string message = "Hello over UDP";
        const auto sent = sendto(socket.get(), message.data(), static_cast<int>(message.size()), 0,
                                 reinterpret_cast<const sockaddr*>(&destination), sizeof(destination));
        if (sent < 0) net::fail("sendto");
        if (sent != static_cast<int>(message.size())) throw std::runtime_error("incomplete datagram");
        net::waitReady(socket, false, net::after(std::chrono::seconds(3)));
        char buffer[1024]{};
        sockaddr_in sender{};
        net::AddressLength length = sizeof(sender);
        const auto count = recvfrom(socket.get(), buffer, sizeof(buffer), 0,
                                    reinterpret_cast<sockaddr*>(&sender), &length);
        if (count < 0) net::fail("recvfrom");
        if (sender.sin_addr.s_addr != destination.sin_addr.s_addr || sender.sin_port != destination.sin_port)
            throw std::runtime_error("unexpected sender");
        const std::string reply(buffer, static_cast<std::size_t>(count));
        std::cout << "Datagram echo: " << reply << '\n';
        return reply == message ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
