#include "../common/net.hpp"
#include <iostream>
#include <future>
#include <mutex>
#include <vector>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42009, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        std::mutex outputMtx;
        std::vector<std::future<void>> jobs;
        for (int i = 0; i < 3; ++i)
        {
            auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
            jobs.push_back(std::async(std::launch::async,
                [client = std::move(client), &outputMtx]() {
                    const auto message = net::receiveLine(client, net::after(std::chrono::seconds(3)));
                    net::sendAll(client, message + '\n', net::after(std::chrono::seconds(3)));
                    std::lock_guard<std::mutex> guard(outputMtx);
                    std::cout << "Handled: " << message << '\n';
                }));
        }
        for (auto& job : jobs) job.get(); // Ожидание завершения и получение исключений.
        std::cout << "Handled clients: 3\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
