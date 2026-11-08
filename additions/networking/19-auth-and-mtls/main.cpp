// C++11 — RAII; libcurl — взаимная проверка TLS-сертификатов.
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

#include <curl/curl.h>

#include "../common/curl_client.hpp"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 5) throw std::runtime_error("Usage: main https-url ca.pem client.pem client.key");
        if (std::string(argv[1]).rfind("https://", 0) != 0) throw std::runtime_error("https URL required");
        web::Runtime runtime;
        std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> handle(curl_easy_init(), curl_easy_cleanup);
        if (!handle) throw std::runtime_error("curl_easy_init");
        std::string body;
        web::option(handle.get(), CURLOPT_URL, argv[1]);
        web::option(handle.get(), CURLOPT_CAINFO, argv[2]);
        web::option(handle.get(), CURLOPT_SSLCERT, argv[3]);
        web::option(handle.get(), CURLOPT_SSLKEY, argv[4]);
        web::option(handle.get(), CURLOPT_SSL_VERIFYPEER, 1L);
        web::option(handle.get(), CURLOPT_SSL_VERIFYHOST, 2L);
        web::option(handle.get(), CURLOPT_NOPROXY, "127.0.0.1,localhost");
        web::option(handle.get(), CURLOPT_CONNECTTIMEOUT_MS, 1000L);
        web::option(handle.get(), CURLOPT_TIMEOUT_MS, 3000L);
        web::option(handle.get(), CURLOPT_WRITEFUNCTION, web::collect);
        web::option(handle.get(), CURLOPT_WRITEDATA, &body);
        const auto result = curl_easy_perform(handle.get());
        if (result != CURLE_OK) throw std::runtime_error(curl_easy_strerror(result));
        long status = 0;
        if (curl_easy_getinfo(handle.get(), CURLINFO_RESPONSE_CODE, &status) != CURLE_OK || status != 200) return 1;
        std::cout << "mTLS 200: " << body << "\nOK reference-example\n";
    }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
