#ifndef NETWORKING_DEMO_HTTP_HPP
#define NETWORKING_DEMO_HTTP_HPP

#include "net.hpp"

#include <cctype>
#include <regex>
#include <sstream>

// Ограниченный HTTP/1.x для локальных учебных серверов:
// один запрос на соединение, Content-Length, заголовки до 8 КиБ, тело до 4 КиБ.
// Chunked, keep-alive и TLS на стороне этих серверов не реализованы.
namespace http
{
struct Request
{
    std::string method;
    std::string path;
    std::string body;
    std::string contentType;
};

inline std::string trim(std::string text)
{
    const auto first = text.find_first_not_of(" \t\r");
    if (first == std::string::npos) return {};
    const auto last = text.find_last_not_of(" \t\r");
    return text.substr(first, last - first + 1);
}

inline std::string lower(std::string text)
{
    for (char& ch : text)
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    return text;
}

inline Request receive(const net::Socket& socket, net::Deadline deadline)
{
    Request request;
    const std::string firstLine = net::receiveLine(socket, deadline, 8192);
    std::istringstream first(firstLine);
    std::string version;
    std::string extra;
    if (!(first >> request.method >> request.path >> version) || first >> extra
        || (version != "HTTP/1.1" && version != "HTTP/1.0"))
        throw std::runtime_error("invalid HTTP request line");

    std::size_t contentLength = 0;
    std::size_t headerSize = firstLine.size() + 1;
    bool hasLength = false;
    for (;;)
    {
        std::string line = net::receiveLine(socket, deadline, 8192);
        headerSize += line.size() + 1;
        if (headerSize > 8192) throw std::runtime_error("HTTP headers are too large");
        if (line == "\r" || line.empty()) break;
        const auto colon = line.find(':');
        if (colon == std::string::npos) throw std::runtime_error("invalid HTTP header");
        const std::string name = lower(trim(line.substr(0, colon)));
        const std::string value = trim(line.substr(colon + 1));
        if (name == "transfer-encoding")
            throw std::runtime_error("Transfer-Encoding is not supported in this demo");
        if (name == "content-type") request.contentType = lower(value);
        if (name == "content-length")
        {
            const auto parsed = std::from_chars(value.data(), value.data() + value.size(), contentLength);
            if (hasLength || parsed.ec != std::errc{} || parsed.ptr != value.data() + value.size()
                || contentLength > 4096)
                throw std::runtime_error("invalid or excessive Content-Length");
            hasLength = true;
        }
    }
    request.body = net::receiveExact(socket, contentLength, deadline);
    return request;
}

inline void respond(const net::Socket& socket, int status, std::string_view body,
                    net::Deadline deadline, std::string_view extraHeaders = {})
{
    const char* reason = "Error";
    switch (status)
    {
    case 200: reason = "OK"; break;
    case 201: reason = "Created"; break;
    case 204: reason = "No Content"; break;
    case 400: reason = "Bad Request"; break;
    case 404: reason = "Not Found"; break;
    case 405: reason = "Method Not Allowed"; break;
    }
    std::string response = "HTTP/1.1 " + std::to_string(status) + " " + reason
        + "\r\nContent-Type: application/json\r\nConnection: close\r\n";
    // У ответа 204 тела нет; Content-Length для него не посылается.
    if (status != 204) response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
    response.append(extraHeaders);
    response += "\r\n";
    if (status != 204) response.append(body);
    net::sendAll(socket, response, deadline);
}

inline bool parseValue(const std::string& json, int& result)
{
    // Поддерживается только схема {"value": целое_число}, не произвольный JSON.
    const std::regex pattern(R"(\s*\{\s*"value"\s*:\s*(-?(?:0|[1-9][0-9]*))\s*\}\s*)");
    std::smatch match;
    if (!std::regex_match(json, match, pattern)) return false;
    const std::string number = match[1].str();
    const auto parsed = std::from_chars(number.data(), number.data() + number.size(), result);
    return parsed.ec == std::errc{} && parsed.ptr == number.data() + number.size();
}
} // namespace http
#endif
