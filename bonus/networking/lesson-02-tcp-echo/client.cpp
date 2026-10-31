#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        const auto port = net::portArgument(argc, argv, 42002);
        auto socket = net::connectLoopback(port, net::after(std::chrono::seconds(2)));
        const std::string message = "Hello over TCP";
        net::sendAll(socket, message + '\n', net::after(std::chrono::seconds(3)));
        const auto reply = net::receiveLine(socket, net::after(std::chrono::seconds(3)));
        std::cout << "Echo: " << reply << '\n';
        return reply == message ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
