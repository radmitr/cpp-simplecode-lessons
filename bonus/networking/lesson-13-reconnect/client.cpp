#include "retry.hpp"
#include <future>
#include <iostream>
#include <thread>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        if (argc > 3 || (argc == 3 && std::string(argv[2]) != "--cancel"))
            throw std::runtime_error("Usage: client [port] [--cancel]");
        const auto port = argc >= 2 ? net::parsePort(argv[1]) : 42013;
        const bool cancelDemo = argc == 3;
        RetryControl control;
        std::future<void> stopJob;
        if (cancelDemo)
        {
            stopJob = std::async(std::launch::async, [&]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(150));
                control.cancel();
            });
        }
        try
        {
            auto socket = connectWithRetry(static_cast<std::uint16_t>(port), control);
            net::sendAll(socket, "Connected after retry\n", net::after(std::chrono::seconds(2)));
            const auto reply = net::receiveLine(socket, net::after(std::chrono::seconds(2)));
            std::cout << reply << '\n';
            return reply == "Connected after retry" ? 0 : 1;
        }
        catch (const Cancelled&)
        {
            std::cout << "Retry cancelled\n";
            return cancelDemo ? 0 : 1;
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
