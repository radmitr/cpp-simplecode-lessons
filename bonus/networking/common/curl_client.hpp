#ifndef NETWORKING_DEMO_CURL_CLIENT_HPP
#define NETWORKING_DEMO_CURL_CLIENT_HPP

#include <curl/curl.h>

#include <cstddef>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

namespace web
{
class Runtime
{
public:
    Runtime()
    {
        if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK)
            throw std::runtime_error("curl_global_init failed");
    }
    ~Runtime() { curl_global_cleanup(); }
    Runtime(const Runtime&) = delete;
    Runtime& operator=(const Runtime&) = delete;
};

struct Response
{
    long status = 0;
    std::string body;
};

inline std::size_t collect(char* data, std::size_t size, std::size_t count, void* user) noexcept
{
    auto& body = *static_cast<std::string*>(user);
    constexpr std::size_t limit = 65536;
    if (size != 0 && count > limit / size) return 0;
    const auto bytes = size * count;
    if (bytes > limit - body.size()) return 0;
    try
    {
        body.append(data, bytes);
        return bytes;
    }
    catch (...)
    {
        return 0; // Исключения C++ не должны пересекать границу C callback.
    }
}

template <typename T>
inline void option(CURL* handle, CURLoption name, T value)
{
    const auto result = curl_easy_setopt(handle, name, value);
    if (result != CURLE_OK) throw std::runtime_error(curl_easy_strerror(result));
}

inline Response request(const std::string& method, const std::string& url,
                        const std::string& body = {}, const std::string& caFile = {})
{
    std::unique_ptr<CURL, decltype(&curl_easy_cleanup)> handle(curl_easy_init(), curl_easy_cleanup);
    if (!handle) throw std::runtime_error("curl_easy_init failed");
    std::unique_ptr<curl_slist, decltype(&curl_slist_free_all)> headers(
        curl_slist_append(nullptr, "Content-Type: application/json"), curl_slist_free_all);
    if (!headers) throw std::runtime_error("curl_slist_append failed");

    Response response;
    option(handle.get(), CURLOPT_URL, url.c_str());
    option(handle.get(), CURLOPT_CONNECTTIMEOUT_MS, 1000L);
    option(handle.get(), CURLOPT_TIMEOUT_MS, 3000L);
    option(handle.get(), CURLOPT_NOSIGNAL, 1L);
    option(handle.get(), CURLOPT_NOPROXY, "127.0.0.1,localhost");
    option(handle.get(), CURLOPT_WRITEFUNCTION, collect);
    option(handle.get(), CURLOPT_WRITEDATA, &response.body);
    option(handle.get(), CURLOPT_SSL_VERIFYPEER, 1L);
    option(handle.get(), CURLOPT_SSL_VERIFYHOST, 2L);
    if (!caFile.empty()) option(handle.get(), CURLOPT_CAINFO, caFile.c_str());
    if (method != "GET")
    {
        option(handle.get(), CURLOPT_HTTPHEADER, headers.get());
        option(handle.get(), CURLOPT_POSTFIELDS, body.c_str());
        option(handle.get(), CURLOPT_POSTFIELDSIZE, static_cast<long>(body.size()));
        option(handle.get(), CURLOPT_CUSTOMREQUEST, method.c_str());
    }

    const auto result = curl_easy_perform(handle.get());
    if (result != CURLE_OK) throw std::runtime_error(curl_easy_strerror(result));
    const auto info = curl_easy_getinfo(handle.get(), CURLINFO_RESPONSE_CODE, &response.status);
    if (info != CURLE_OK) throw std::runtime_error(curl_easy_strerror(info));
    return response;
}
} // namespace web
#endif
