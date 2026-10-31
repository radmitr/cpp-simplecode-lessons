#include "../common/http.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42007, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
        const auto request = http::receive(client, net::after(std::chrono::seconds(3)));
        std::cout << request.method << ' ' << request.path << "\nBody: " << request.body << '\n';
        int value = 0;
        if (request.method != "POST")
            http::respond(client, 405, R"({"error":"use POST"})", net::after(std::chrono::seconds(3)),
                          "Allow: POST\r\n");
        else if (request.path != "/config")
            http::respond(client, 404, R"({"error":"not found"})", net::after(std::chrono::seconds(3)));
        else if (request.contentType != "application/json" || !http::parseValue(request.body, value))
            http::respond(client, 400, R"({"error":"expected JSON integer value"})",
                          net::after(std::chrono::seconds(3)));
        else
            http::respond(client, 200, R"({"accepted":true,"value":)" + std::to_string(value) + "}",
                          net::after(std::chrono::seconds(3)));
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
