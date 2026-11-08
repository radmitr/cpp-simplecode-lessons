// C++20 — std::source_location и место вызова аргумента по умолчанию.
#include <cstdint>
#include <exception>
#include <iostream>
#include <source_location>
#include <string_view>

#include "../../../basics/bonus/common/check.hpp"

std::source_location capture(std::source_location where = std::source_location::current())
{
    return where;
}
std::source_location wrapper(std::source_location where = std::source_location::current())
{
    return capture(where);
}

int main()
{
    try
    {
        const auto expected = static_cast<std::uint_least32_t>(__LINE__ + 1);
        const auto direct = capture();
        check(direct.line() == expected, "default argument records caller");
        const auto wrapper_line = static_cast<std::uint_least32_t>(__LINE__ + 1);
        const auto forwarded = wrapper();
        check(forwarded.line() == wrapper_line, "wrapper forwards original location");
        check(std::string_view(direct.file_name()).find("main.cpp") != std::string_view::npos, "file name");
        check(std::string_view(direct.function_name()).size() > 0, "function name");
        std::cout << "caller captured: " << direct.line() << ' ' << direct.column() << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
