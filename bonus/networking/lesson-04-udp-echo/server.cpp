#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto socket = net::makeSocket(SOCK_DGRAM);
        net::bindLoopback(socket, net::portArgument(argc, argv, 42004, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(socket) << std::endl;
        net::waitReady(socket, false, net::after(std::chrono::seconds(15)));
        sockaddr_in sender{};
        net::AddressLength length = sizeof(sender);
        char buffer[1024]{};
        const auto count = recvfrom(socket.get(), buffer, sizeof(buffer), 0,
                                    reinterpret_cast<sockaddr*>(&sender), &length);
        if (count < 0) net::fail("recvfrom");
        // У UDP даже нулевая длина может означать полноценную пустую датаграмму.
        const auto sent = sendto(socket.get(), buffer, static_cast<int>(count), 0,
                                 reinterpret_cast<const sockaddr*>(&sender), length);
        if (sent < 0) net::fail("sendto");
        if (sent != count) throw std::runtime_error("incomplete datagram");
        std::cout << "Echoed datagram: " << count << " bytes\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
