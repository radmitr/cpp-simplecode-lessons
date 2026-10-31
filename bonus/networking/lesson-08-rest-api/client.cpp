#include "../common/curl_client.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        web::Runtime runtime;
        if (argc > 2) throw std::runtime_error("Usage: client [base-url]");
        const std::string base = argc == 2 ? argv[1] : "http://127.0.0.1:42008";
        auto check = [&](const char* method, const char* path, const std::string& body,
                         long expectedStatus, const std::string& expectedBody) {
            const auto response = web::request(method, base + path, body);
            std::cout << method << ' ' << path << " -> " << response.status << ' ' << response.body << '\n';
            if (response.status != expectedStatus || response.body != expectedBody)
                throw std::runtime_error("unexpected API response; restart the demo server");
        };
        check("POST", "/items", R"({"value":42})", 201, R"({"id":1,"value":42})");
        check("GET", "/items/1", "", 200, R"({"id":1,"value":42})");
        check("PUT", "/items/1", R"({"value":7})", 200, R"({"id":1,"value":7})");
        check("DELETE", "/items/1", "", 204, "");
        check("GET", "/items/1", "", 404, R"({"error":"not found"})");
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
