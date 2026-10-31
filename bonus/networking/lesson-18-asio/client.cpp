#include "../common/net.hpp"
#include <future>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        const auto port = net::portArgument(argc, argv, 42018);
        std::vector<std::future<void>> jobs;
        for (int id = 1; id <= 3; ++id)
        {
            jobs.push_back(std::async(std::launch::async, [port, id]() {
                auto socket = net::connectLoopback(port, net::after(std::chrono::seconds(2)));
                const auto message = "async client " + std::to_string(id);
                net::sendAll(socket, message + '\n', net::after(std::chrono::seconds(3)));
                if (net::receiveLine(socket, net::after(std::chrono::seconds(3))) != message)
                    throw std::runtime_error("async echo does not match");
            }));
        }
        for (auto& job : jobs) job.get();
        std::cout << "Async echo verified: 3 clients\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
