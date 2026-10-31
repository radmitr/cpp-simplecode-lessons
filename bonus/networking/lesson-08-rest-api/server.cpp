#include "../common/http.hpp"
#include <iostream>
#include <map>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        auto listener = net::listenTcp(net::portArgument(argc, argv, 42008, true));
        std::cout << "Listening on 127.0.0.1:" << net::localPort(listener) << std::endl;
        std::map<int, int> items;
        int nextId = 1;
        // Клиент делает пять запросов: POST, GET, PUT, DELETE, GET.
        for (int i = 0; i < 5; ++i)
        {
            auto client = net::accept(listener, net::after(std::chrono::seconds(15)));
            const auto request = http::receive(client, net::after(std::chrono::seconds(3)));
            int status = 404;
            std::string body = R"({"error":"not found"})";
            std::string headers;
            int value = 0;
            if (request.path == "/items")
            {
                if (request.method != "POST")
                {
                    status = 405;
                    body = R"({"error":"method not allowed"})";
                    headers = "Allow: POST\r\n";
                }
                else if (request.contentType != "application/json" || !http::parseValue(request.body, value))
                {
                    status = 400;
                    body = R"({"error":"expected JSON integer value"})";
                }
                else
                {
                    const int id = nextId++;
                    items[id] = value;
                    status = 201;
                    body = R"({"id":)" + std::to_string(id) + R"(,"value":)" + std::to_string(value) + "}";
                    headers = "Location: /items/" + std::to_string(id) + "\r\n";
                }
            }
            else if (request.path.compare(0, 7, "/items/") == 0)
            {
                int id = 0;
                const std::string text = request.path.substr(7);
                const auto parsed = std::from_chars(text.data(), text.data() + text.size(), id);
                const auto item = items.find(id);
                if (parsed.ec == std::errc{} && parsed.ptr == text.data() + text.size() && item != items.end())
                {
                    if (request.method == "GET")
                    {
                        status = 200;
                        body = R"({"id":)" + std::to_string(id) + R"(,"value":)" + std::to_string(item->second) + "}";
                    }
                    else if (request.method == "PUT")
                    {
                        if (request.contentType != "application/json" || !http::parseValue(request.body, value))
                        {
                            status = 400;
                            body = R"({"error":"expected JSON integer value"})";
                        }
                        else
                        {
                            item->second = value;
                            status = 200;
                            body = R"({"id":)" + std::to_string(id) + R"(,"value":)" + std::to_string(value) + "}";
                        }
                    }
                    else if (request.method == "DELETE")
                    {
                        items.erase(item);
                        status = 204;
                        body.clear();
                    }
                    else
                    {
                        status = 405;
                        body = R"({"error":"method not allowed"})";
                        headers = "Allow: GET, PUT, DELETE\r\n";
                    }
                }
            }
            std::cout << request.method << ' ' << request.path << " -> " << status << '\n';
            http::respond(client, status, body, net::after(std::chrono::seconds(3)), headers);
        }
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
