#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        const auto port = net::portArgument(argc, argv, 42002, true);
        auto listener = net::listenTcp(port); // socket() -> bind(127.0.0.1) -> listen().
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        const auto message = net::receiveLine(client, net::after(std::chrono::seconds(3)));
        std::cout << "Received: " << message << '\n';
        net::sendAll(client, message + '\n', net::after(std::chrono::seconds(3)));
        return 0; // Деструкторы закроют и принятое соединение, и слушающий сокет.
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
