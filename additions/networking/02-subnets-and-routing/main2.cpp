// C++11 — unique_ptr; внешний API — getaddrinfo/getnameinfo.
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>

#include "../common/net.hpp"

int main()
{
    try
    {
        net::Runtime runtime;
        addrinfo hints{};
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        addrinfo* raw = nullptr;
        if (getaddrinfo("localhost", "80", &hints, &raw) != 0) return 1;
        std::unique_ptr<addrinfo, decltype(&freeaddrinfo)> addresses(raw, freeaddrinfo);
        int count = 0;
        for (auto* item = addresses.get(); item; item = item->ai_next)
        {
            char host[NI_MAXHOST]{};
            if (getnameinfo(item->ai_addr, static_cast<net::AddressLength>(item->ai_addrlen),
                host, sizeof(host), nullptr, 0, NI_NUMERICHOST) != 0) return 1;
            std::cout << host << '\n';
            ++count;
        }
        if (count == 0) return 1;
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
