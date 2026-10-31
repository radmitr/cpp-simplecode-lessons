#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42014, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        for (int sequence = 1; sequence <= 3; ++sequence)
        {
            const auto ping = net::receiveLine(client, net::after(std::chrono::seconds(3)));
            if (ping != "PING " + std::to_string(sequence))
                throw std::runtime_error("unexpected heartbeat sequence");
            if (sequence < 3)
                net::sendAll(client, "PONG " + std::to_string(sequence) + '\n',
                             net::after(std::chrono::seconds(2)));
            else
                std::cout << "Simulating an application that no longer replies\n";
        }
        // TCP остаётся открыт, но приложение уже не посылает PONG.
        char byte = '\0';
        if (net::receiveSome(client, &byte, 1, net::after(std::chrono::seconds(5))) != 0)
            throw std::runtime_error("expected client to close after its heartbeat timeout");
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
