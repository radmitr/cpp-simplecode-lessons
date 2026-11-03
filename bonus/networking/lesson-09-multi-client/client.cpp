// C++11 — std::mutex, std::lock_guard, std::future, std::async.
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <vector>

#include "../common/net.hpp"

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        const auto port = net::portArgument(argc, argv, 42009);
        std::mutex outputMtx;
        std::vector<std::future<void>> jobs;
        for (int id = 1; id <= 3; ++id)
        {
            jobs.push_back(std::async(std::launch::async, [port, id, &outputMtx]() {
                auto socket = net::connectLoopback(port, net::after(std::chrono::seconds(2)));
                const auto message = "client " + std::to_string(id);
                net::sendAll(socket, message + '\n', net::after(std::chrono::seconds(3)));
                const auto reply = net::receiveLine(socket, net::after(std::chrono::seconds(3)));
                if (reply != message) throw std::runtime_error("echo does not match");
                std::lock_guard<std::mutex> guard(outputMtx);
                std::cout << "Verified: " << reply << '\n';
            }));
        }
        for (auto& job : jobs) job.get();
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
