// C++11 — std::async, std::future, std::launch и лямбды.
#include "../common/net.hpp"
#include "../../../common/console.hpp"
#include <future>
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();
    try
    {
        net::Runtime runtime;
        const auto port = net::portArgument(argc, argv, 42021);
        std::vector<std::future<void>> clients;
        for (int id = 1; id <= 3; ++id)
            clients.push_back(std::async(std::launch::async, [port, id]() {
                auto socket = net::connectLoopback(port, net::after(std::chrono::seconds(2)));
                for (int sequence = 1; sequence <= 3; ++sequence)
                {
                    const auto text = "client-" + std::to_string(id);
                    net::sendAll(socket, text + '\n', net::after(std::chrono::seconds(2)));
                    const auto reply = net::receiveLine(socket, net::after(std::chrono::seconds(2)));
                    if (reply != std::to_string(sequence) + ":" + text)
                        throw std::runtime_error("Нарушен порядок ответов сессии");
                }
            }));
        for (auto& client : clients) client.get();
        std::cout << "Strand verified: 3 clients, 9 ordered replies\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}
