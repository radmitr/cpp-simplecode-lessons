// C++23 — форматирование диапазонов и tuple, std::print/println.
#include <exception>
#include <format>
#include <iostream>
#include <print>
#include <string>
#include <tuple>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::vector values{1, 2, 3};
        const auto text = std::format("{}", values);
        check(text == "[1, 2, 3]", "range format");
        const auto pair = std::tuple{7, std::string("Ada")};
        std::print("{} | ", text);
        std::println("{}", pair);
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
