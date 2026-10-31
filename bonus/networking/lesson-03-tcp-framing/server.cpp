#include "../common/net.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42003, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        for (int i = 0; i < 3; ++i)
        {
            // Сначала ровно 4 байта длины, затем ровно указанное количество байтов.
            const auto frame = net::receiveFrame(client, net::after(std::chrono::seconds(3)));
            std::cout << "Frame " << i + 1 << ": " << frame.size() << " bytes\n";
            net::sendFrame(client, frame, net::after(std::chrono::seconds(3)));
        }
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
