#include "../common/curl_client.hpp"
#include <iostream>

int main(int argc, char* argv[])
{
    try
    {
        web::Runtime runtime;
        if (argc > 3) throw std::runtime_error("Usage: main [https-url] [ca-certificate.pem]");
        const std::string url = argc >= 2 ? argv[1] : "https://example.com/";
        if (url.compare(0, 8, "https://") != 0) throw std::runtime_error("Use an https:// URL");
        const std::string caFile = argc == 3 ? argv[2] : "";
        // libcurl выполняет TLS handshake и проверяет сертификат и имя сервера.
        const auto response = web::request("GET", url, "", caFile);
        std::cout << "HTTPS status: " << response.status
                  << "\nReceived bytes: " << response.body.size() << '\n';
        return response.status == 200 ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
