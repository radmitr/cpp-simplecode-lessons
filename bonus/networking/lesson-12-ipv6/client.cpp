#include "../common/resolved_address.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        if (argc > 3) throw std::runtime_error("Usage: client [port] [hostname]");
        const auto port = argc >= 2 ? net::parsePort(argv[1]) : 42012;
        const std::string hostname = argc == 3 ? argv[2] : "localhost";
        // Результаты getaddrinfo() могут содержать оба семейства: пробуем по очереди.
        auto socket = net::connectHost(hostname, static_cast<std::uint16_t>(port),
                                       net::after(std::chrono::seconds(3)));
        net::sendAll(socket, "Hello over IPv6\n", net::after(std::chrono::seconds(3)));
        const auto reply = net::receiveLine(socket, net::after(std::chrono::seconds(3)));
        std::cout << "IPv6 echo: " << reply << '\n';
        return reply == "Hello over IPv6" ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
