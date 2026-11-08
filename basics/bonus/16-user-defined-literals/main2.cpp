// C++11 — строковый пользовательский литерал с длиной.
#include <cstddef>
#include <exception>
#include <iostream>

#include "../../../basics/bonus/common/check.hpp"

namespace text
{
    struct Text { const char* data; std::size_t size; };
    constexpr Text operator""_text(const char* data, std::size_t size) { return Text{data, size}; }
}

int main()
{
    try
    {
        using namespace text;
        constexpr auto value = "a\0b"_text;
        static_assert(value.size == 3 && value.data[1] == '\0', "embedded zero");
        const auto letter = 'A';
        check(letter == value.data[0] - ('a' - 'A'), "literal character data");
        std::cout << value.size << ' ' << value.data[2] << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
