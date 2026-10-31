#include "../common/curl_client.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        web::Runtime runtime;
        if (argc > 2) throw std::runtime_error("Usage: client [url]");
        const std::string url = argc == 2 ? argv[1] : "http://127.0.0.1:42007/config";
        const auto response = web::request("POST", url, R"({"value":42})");
        std::cout << "HTTP status: " << response.status << "\nBody: " << response.body << '\n';
        return response.status == 200 && response.body == R"({"accepted":true,"value":42})" ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
