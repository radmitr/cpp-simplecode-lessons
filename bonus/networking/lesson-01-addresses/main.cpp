#include "../common/net.hpp"
#include <iostream>
#include <memory>

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime; // На Windows вызывает WSAStartup(), на Linux ничего не требуется.
        if (argc > 2) throw std::runtime_error("Usage: main [hostname]");
        const char* hostname = argc == 2 ? argv[1] : "localhost";
        addrinfo hints{};
        hints.ai_family = AF_UNSPEC; // Разрешены IPv4 и IPv6.
        hints.ai_socktype = SOCK_STREAM;
        addrinfo* raw = nullptr;
        const int error = getaddrinfo(hostname, "80", &hints, &raw);
        if (error != 0) throw std::runtime_error("getaddrinfo failed: " + std::to_string(error));
        std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> addresses(raw, freeaddrinfo);

        int found = 0;
        for (const addrinfo* entry = addresses.get(); entry; entry = entry->ai_next)
        {
            const void* address = nullptr;
            if (entry->ai_family == AF_INET)
                address = &reinterpret_cast<const sockaddr_in*>(entry->ai_addr)->sin_addr;
            else if (entry->ai_family == AF_INET6)
                address = &reinterpret_cast<const sockaddr_in6*>(entry->ai_addr)->sin6_addr;
            else
                continue;
            char text[INET6_ADDRSTRLEN]{};
            if (!inet_ntop(entry->ai_family, address, text, sizeof(text))) net::fail("inet_ntop");
            std::cout << (entry->ai_family == AF_INET ? "IPv4: " : "IPv6: ") << text << '\n';
            ++found;
        }
        std::cout << "Port 80 -> network byte order -> " << ntohs(htons(80)) << '\n';
        return found > 0 ? 0 : 1;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
