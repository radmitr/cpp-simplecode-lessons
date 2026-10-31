#include "../common/net.hpp"
#include <iostream>
#include <array>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto socket = net::connectLoopback(net::portArgument(argc, argv, 42003),
                                           net::after(std::chrono::seconds(2)));
        const std::array<std::string, 3> messages{"Hello", "", std::string("A\0B", 3)};
        for (const auto& message : messages)
        {
            // sendFrame() специально ограничивает один send() тремя байтами.
            net::sendFrame(socket, message, net::after(std::chrono::seconds(3)));
            const auto reply = net::receiveFrame(socket, net::after(std::chrono::seconds(3)));
            if (reply != message) throw std::runtime_error("frame does not match");
            std::cout << "Verified frame: " << reply.size() << " bytes\n";
        }
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
