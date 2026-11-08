// C++20 — designated initializers; C++11 — значения полей по умолчанию.
#include <exception>
#include <iostream>
#include <string>

#include "../../../basics/bonus/common/check.hpp"

struct Options
{
    std::string name = "guest";
    int port = 8080;
    int retries = 3;
};

int main()
{
    try
    {
        const Options selected{.name = "Ada", .retries = 5};
        check(selected.port == 8080 && selected.retries == 5, "omitted member uses default");
        const Options defaults{};
        check(defaults.name == "guest" && defaults.retries == 3, "default member initializers");
        std::cout << selected.name << ' ' << selected.port << ' ' << selected.retries << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
