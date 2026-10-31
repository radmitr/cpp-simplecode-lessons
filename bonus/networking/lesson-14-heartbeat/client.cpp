#include "../common/net.hpp"
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto socket = net::connectLoopback(net::portArgument(argc, argv, 42014),
                                           net::after(std::chrono::seconds(2)));
        for (int sequence = 1; sequence <= 3; ++sequence)
        {
            net::sendAll(socket, "PING " + std::to_string(sequence) + '\n',
                         net::after(std::chrono::seconds(2)));
            try
            {
                const auto pong = net::receiveLine(socket, net::after(std::chrono::milliseconds(250)));
                if (pong != "PONG " + std::to_string(sequence))
                    throw std::runtime_error("unexpected PONG");
                std::cout << pong << '\n';
            }
            catch (const net::Timeout&)
            {
                std::cout << "Heartbeat timeout: peer application is not responding\n";
                return sequence == 3 ? 0 : 1;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        throw std::runtime_error("the demo server should skip its third PONG");
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
