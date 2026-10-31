#include "../common/net.hpp"
#include <iostream>
#include <map>
#include <sstream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42015, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        struct Record { int amount; int result; };
        std::map<std::string, Record> completed;
        int total = 0;
        int applications = 0;
        for (int attempt = 0; attempt < 3; ++attempt)
        {
            auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
            const auto message = net::receiveLine(client, net::after(std::chrono::seconds(3)));
            std::istringstream input(message);
            std::string operation, id, extra;
            int amount = 0;
            if (!(input >> operation >> id >> amount) || input >> extra || operation != "ADD"
                || id.size() > 32 || amount < -1000 || amount > 1000)
                throw std::runtime_error("expected ADD request_id amount (-1000..1000)");

            const auto previous = completed.find(id);
            std::string response;
            if (previous != completed.end())
            {
                response = previous->second.amount == amount
                    ? "ACK " + id + " " + std::to_string(previous->second.result)
                    : "ERROR " + id + " conflict";
            }
            else
            {
                total += amount;
                ++applications;
                completed.emplace(id, Record{amount, total});
                response = "ACK " + id + " " + std::to_string(total);
                if (attempt == 0)
                {
                    std::cout << "Applied " << id << "; simulating lost ACK\n";
                    continue; // Закрываем соединение без ответа после выполнения команды.
                }
            }
            net::sendAll(client, response + '\n', net::after(std::chrono::seconds(2)));
        }
        std::cout << "Applications: " << applications << "\nTotal: " << total << '\n';
        return applications == 1 && total == 5 ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
