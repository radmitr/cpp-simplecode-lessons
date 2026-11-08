// C++23 — spanstream и ограничение буфера.
#include <array>
#include <exception>
#include <iostream>
#include <span>
#include <spanstream>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::array<char, 2> small{};
        std::ospanstream limited{std::span<char>(small)};
        limited << "abc";
        check(limited.fail(), "fixed buffer overflow");
        std::array<char, 16> storage{};
        std::spanstream both{std::span<char>(storage)};
        both << 42;
        both.seekg(0);
        int value = 0;
        both >> value;
        check(value == 42, "separate get position");
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
