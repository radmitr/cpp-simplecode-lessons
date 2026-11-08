// C++17 — string_view; HTTP — аутентификация и авторизация демонстрационных ролей.
#include <chrono>
#include <exception>
#include <iostream>
#include <string>

#include "../common/http.hpp"
#include "../common/net.hpp"

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42026, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        for (int request = 0; request < 4; ++request)
        {
            auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
            const auto deadline = net::after(std::chrono::seconds(3));
            const auto input = http::receive(client, deadline);
            const bool reader = input.authorization == "Bearer demo-reader";
            const bool writer = input.authorization == "Bearer demo-writer";
            const int status = !reader && !writer ? 401 : input.method != "GET" && !writer ? 403 : 200;
            http::respond(client, status, "{\"status\":" + std::to_string(status) + "}", deadline,
                status == 401 ? "WWW-Authenticate: Bearer\r\n" : "");
        }
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
