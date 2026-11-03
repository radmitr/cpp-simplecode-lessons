// C++11 — std::unique_ptr; HTTP/2 и HTTP/3 предоставляет libcurl.
#include "../common/curl_client.hpp"
#include "../../../common/console.hpp"
#include <iostream>

#if LIBCURL_VERSION_NUM < 0x075800
#error This lesson requires libcurl headers 7.88.0 or newer
#endif

int main(int argc, char* argv[])
{
    console::setupConsoleEncoding();
    try
    {
        web::Runtime runtime;
        const auto* version = curl_version_info(CURLVERSION_NOW);
        const bool h2 = (version->features & CURL_VERSION_HTTP2) != 0;
        const bool h3 = (version->features & CURL_VERSION_HTTP3) != 0;
        std::cout << "libcurl " << version->version << "; HTTP2=" << h2 << "; HTTP3=" << h3 << '\n';
        if (argc == 2 && std::string(argv[1]) == "--features") return 0;
        if (argc < 3 || argc > 4)
            throw std::runtime_error("Использование: main h1|h2|h2-only|h3|h3-only URL [ca.pem]");
        const std::string mode = argv[1];
        const std::string url = argv[2];
        if (url.compare(0, 7, "http://") != 0 && url.compare(0, 8, "https://") != 0)
            throw std::runtime_error("Нужен URL http:// или https://");
        long requested = CURL_HTTP_VERSION_1_1;
        if (mode == "h2") requested = CURL_HTTP_VERSION_2TLS;
        else if (mode == "h2-only") requested = CURL_HTTP_VERSION_2_PRIOR_KNOWLEDGE;
        else if (mode == "h3") requested = CURL_HTTP_VERSION_3;
        else if (mode == "h3-only") requested = CURL_HTTP_VERSION_3ONLY;
        else if (mode != "h1") throw std::runtime_error("Неизвестный режим HTTP");
        if ((mode == "h2" || mode == "h2-only") && !h2)
            throw std::runtime_error("Эта libcurl собрана без HTTP/2");
        if ((mode == "h3" || mode == "h3-only") && (!h3 || url.compare(0, 8, "https://") != 0))
            throw std::runtime_error("Для HTTP/3 нужны поддержка в libcurl и URL https://");
        std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> handle(curl_easy_init(), curl_easy_cleanup);
        if (!handle) throw std::runtime_error("curl_easy_init failed");
        std::string body;
        web::option(handle.get(), CURLOPT_URL, url.c_str());
        web::option(handle.get(), CURLOPT_HTTP_VERSION, requested);
        web::option(handle.get(), CURLOPT_CONNECTTIMEOUT_MS, 2000L);
        web::option(handle.get(), CURLOPT_TIMEOUT_MS, 5000L);
        web::option(handle.get(), CURLOPT_NOSIGNAL, 1L);
        web::option(handle.get(), CURLOPT_NOPROXY, "localhost,127.0.0.1");
        web::option(handle.get(), CURLOPT_SSL_VERIFYPEER, 1L);
        web::option(handle.get(), CURLOPT_SSL_VERIFYHOST, 2L);
        web::option(handle.get(), CURLOPT_SSLVERSION, static_cast<long>(CURL_SSLVERSION_TLSv1_2));
        if (argc == 4) web::option(handle.get(), CURLOPT_CAINFO, argv[3]);
        web::option(handle.get(), CURLOPT_WRITEFUNCTION, web::collect);
        web::option(handle.get(), CURLOPT_WRITEDATA, &body);
        const auto result = curl_easy_perform(handle.get());
        if (result != CURLE_OK) throw std::runtime_error(curl_easy_strerror(result));
        long actual = 0;
        long status = 0;
        if (curl_easy_getinfo(handle.get(), CURLINFO_HTTP_VERSION, &actual) != CURLE_OK
            || curl_easy_getinfo(handle.get(), CURLINFO_RESPONSE_CODE, &status) != CURLE_OK)
            throw std::runtime_error("Не удалось прочитать версию или статус HTTP");
        const char* label = actual == CURL_HTTP_VERSION_3 ? "3"
            : actual == CURL_HTTP_VERSION_2_0 ? "2"
            : actual == CURL_HTTP_VERSION_1_1 ? "1.1" : actual == CURL_HTTP_VERSION_1_0 ? "1.0" : "?";
        std::cout << "Negotiated HTTP/" << label << "; status " << status << '\n';
        std::cout << "Body bytes: " << body.size() << '\n';
        if ((mode == "h2-only" && actual != CURL_HTTP_VERSION_2_0)
            || (mode == "h3-only" && actual != CURL_HTTP_VERSION_3))
            throw std::runtime_error("Согласованная версия не соответствует строгому режиму");
        return status >= 200 && status < 300 ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }
}
