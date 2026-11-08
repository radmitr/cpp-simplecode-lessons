// C++20 — специализация std::formatter; C++23 — std::println.
#include <exception>
#include <format>
#include <iostream>
#include <print>

#include "../../../basics/additions/common/check.hpp"

struct Point { int x; int y; };
template<> struct std::formatter<Point>
{
    constexpr auto parse(std::format_parse_context& context)
    {
        auto it = context.begin();
        if (it != context.end() && *it != '}') throw std::format_error("Point accepts no format options");
        return it;
    }
    auto format(const Point& p, std::format_context& context) const
    {
        return std::format_to(context.out(), "({}, {})", p.x, p.y);
    }
};

int main()
{
    try
    {
        check(std::format("{}", Point{2, 3}) == "(2, 3)", "custom formatter");
        std::println("{}", Point{2, 3});
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
