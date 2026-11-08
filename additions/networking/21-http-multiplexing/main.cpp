// C++11 — RAII; libcurl multi — одновременная обработка нескольких передач.
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#include <curl/curl.h>

#include "../common/curl_client.hpp"

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 3 && argc != 4) throw std::runtime_error("Usage: main URL1 URL2 [ca.pem]");
        web::Runtime runtime;
        std::unique_ptr<CURLM, decltype(&curl_multi_cleanup)> multi(curl_multi_init(), curl_multi_cleanup);
        if (!multi) throw std::runtime_error("curl_multi_init");
        auto multi_check = [](CURLMcode code) { if (code != CURLM_OK) throw std::runtime_error(curl_multi_strerror(code)); };
        multi_check(curl_multi_setopt(multi.get(), CURLMOPT_PIPELINING, CURLPIPE_MULTIPLEX));
        multi_check(curl_multi_setopt(multi.get(), CURLMOPT_MAX_HOST_CONNECTIONS, 1L));
        std::vector<std::unique_ptr<CURL, decltype(&curl_easy_cleanup)>> handles;
        std::string bodies[2];
        // Удаляем easy handles из multi до их освобождения, в том числе при ошибке.
        struct Remove
        {
            CURLM* multi;
            decltype(handles)& attached;
            ~Remove() { for (auto& handle : attached) if (handle) curl_multi_remove_handle(multi, handle.get()); }
        } remove{multi.get(), handles};
        for (int i = 0; i < 2; ++i)
        {
            handles.emplace_back(curl_easy_init(), curl_easy_cleanup);
            auto* handle = handles.back().get();
            if (!handle) throw std::runtime_error("curl_easy_init");
            web::option(handle, CURLOPT_URL, argv[i + 1]);
            web::option(handle, CURLOPT_HTTP_VERSION, static_cast<long>(CURL_HTTP_VERSION_2TLS));
            web::option(handle, CURLOPT_PIPEWAIT, 1L);
            web::option(handle, CURLOPT_NOPROXY, "127.0.0.1,localhost");
            web::option(handle, CURLOPT_TIMEOUT_MS, 3000L);
            web::option(handle, CURLOPT_WRITEFUNCTION, web::collect);
            web::option(handle, CURLOPT_WRITEDATA, &bodies[i]);
            if (argc == 4) web::option(handle, CURLOPT_CAINFO, argv[3]);
            multi_check(curl_multi_add_handle(multi.get(), handle));
        }
        int running = 0;
        do
        {
            multi_check(curl_multi_perform(multi.get(), &running));
            if (running) multi_check(curl_multi_poll(multi.get(), nullptr, 0, 1000, nullptr));
        } while (running);
        int messages = 0;
        int completed = 0;
        while (auto* message = curl_multi_info_read(multi.get(), &messages))
        {
            if (message->msg != CURLMSG_DONE) continue;
            if (message->data.result != CURLE_OK) throw std::runtime_error(curl_easy_strerror(message->data.result));
            long version = 0;
            long connections = 0;
            long status = 0;
            if (curl_easy_getinfo(message->easy_handle, CURLINFO_HTTP_VERSION, &version) != CURLE_OK
                || curl_easy_getinfo(message->easy_handle, CURLINFO_NUM_CONNECTS, &connections) != CURLE_OK
                || curl_easy_getinfo(message->easy_handle, CURLINFO_RESPONSE_CODE, &status) != CURLE_OK || status != 200) return 1;
            std::cout << "version=" << version << " new_connections=" << connections << '\n';
            ++completed;
        }
        if (completed != 2) return 1;
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
