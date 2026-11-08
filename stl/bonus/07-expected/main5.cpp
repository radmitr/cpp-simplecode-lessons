// C++23 — std::expected<void,E>.
#include <exception>
#include <expected>
#include <iostream>
#include <string>

#include "../../../basics/bonus/common/check.hpp"

std::expected<void, std::string> validate(bool good)
{
    if (!good) return std::unexpected(std::string("rejected"));
    return {};
}

int main()
{
    try
    {
        int calls = 0;
        auto next = [&]() -> std::expected<int, std::string> { ++calls; return 42; };
        check(validate(true).and_then(next).value() == 42, "void success");
        auto failed = validate(false).and_then(next);
        check(!failed && failed.error() == "rejected" && calls == 1, "void failure");
        std::cout << calls << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
