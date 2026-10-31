#include "../common/http.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42006, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        const auto request = http::receive(client, net::after(std::chrono::seconds(3)));
        std::cout << request.method << ' ' << request.path << '\n';
        if (request.method != "GET")
            http::respond(client, 405, R"({"error":"use GET"})", net::after(std::chrono::seconds(3)),
                          "Allow: GET\r\n");
        else if (request.path != "/hello")
            http::respond(client, 404, R"({"error":"not found"})", net::after(std::chrono::seconds(3)));
        else
            http::respond(client, 200, R"({"message":"Hello from HTTP"})",
                          net::after(std::chrono::seconds(3)));
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
