#include "../common/net.hpp"
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        const auto port = net::portArgument(argc, argv, 42013, true);
        std::cout << "Starting after 700 ms..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(700));
        auto listener = net::listenTcp(port);
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        const auto message = net::receiveLine(client, net::after(std::chrono::seconds(3)));
        net::sendAll(client, message + '\n', net::after(std::chrono::seconds(3)));
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
