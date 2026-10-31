#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto socket = net::connectLoopback(net::portArgument(argc, argv, 42005),
                                           net::after(std::chrono::seconds(2)));
        net::sendAll(socket, "Please reply\n", net::after(std::chrono::seconds(2)));
        try
        {
            net::receiveLine(socket, net::after(std::chrono::milliseconds(200)));
            throw std::runtime_error("server unexpectedly replied");
        }
        catch (const net::Timeout&)
        {
            std::cout << "Expected timeout: no response within the deadline\n";
        }
        return 0; // RAII закрывает соединение, сервер увидит recv() == 0.
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
