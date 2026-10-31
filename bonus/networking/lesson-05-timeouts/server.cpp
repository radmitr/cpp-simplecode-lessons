#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42005, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        std::cout << "Request: " << net::receiveLine(client, net::after(std::chrono::seconds(3))) << '\n';
        // Намеренно не отправляем ответ. Ждём закрытия соединения клиентом.
        char byte = '\0';
        const auto count = net::receiveSome(client, &byte, 1, net::after(std::chrono::seconds(5)));
        if (count != 0) throw std::runtime_error("expected peer to close the connection");
        std::cout << "Client closed the connection after its timeout\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
