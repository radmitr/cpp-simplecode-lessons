#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42010, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        std::string latest;
        try
        {
            for (;;)
            {
                latest = net::receiveLine(client, net::after(std::chrono::seconds(3)));
                std::cout << "Received: " << latest << '\n';
            }
        }
        catch (const net::PeerClosed&)
        {
            std::cout << "Sender finished\n";
        }
        return latest == "value=3" ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
