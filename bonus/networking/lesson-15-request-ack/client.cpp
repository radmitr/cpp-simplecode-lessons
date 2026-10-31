#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        const auto port = net::portArgument(argc, argv, 42015);
        auto exchange = [&](const std::string& request) {
            auto socket = net::connectLoopback(port, net::after(std::chrono::seconds(2)));
            net::sendAll(socket, request + '\n', net::after(std::chrono::seconds(2)));
            return net::receiveLine(socket, net::after(std::chrono::seconds(2)));
        };
        try
        {
            exchange("ADD req-1 5");
            throw std::runtime_error("the first ACK should be lost in this demo");
        }
        catch (const net::PeerClosed&)
        {
            std::cout << "ACK was lost; retrying the same request_id and payload\n";
        }
        const auto reply = exchange("ADD req-1 5");
        std::cout << reply << '\n';
        if (reply != "ACK req-1 5") throw std::runtime_error("unexpected result of retry");
        const auto conflict = exchange("ADD req-1 7");
        std::cout << conflict << '\n';
        return conflict == "ERROR req-1 conflict" ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
