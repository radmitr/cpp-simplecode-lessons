#include "../common/curl_client.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        web::Runtime runtime;
        if (argc > 2) throw std::runtime_error("Usage: client [url]");
        const std::string url = argc == 2 ? argv[1] : "http://127.0.0.1:42006/hello";
        const auto response = web::request("GET", url);
        std::cout << "HTTP status: " << response.status << "\nBody: " << response.body << '\n';
        return response.status == 200 ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
