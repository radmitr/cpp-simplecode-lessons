// C++23 — std::generator; C++20 — co_yield и ranges.
#include <exception>
#include <generator>
#include <iostream>
#include <ranges>
#include <utility>
#include <vector>

#include "../../../basics/bonus/common/check.hpp"

std::generator<int> count(int end)
{
    for (int i = 0; i < end; ++i) co_yield i;
}

int main()
{
    try
    {
        auto sequence = count(3);
        auto values = std::move(sequence) | std::views::transform([](int x) { return x * 2; })
            | std::ranges::to<std::vector>();
        check(values == std::vector{0, 2, 4}, "generator range");
        for (int x : values) std::cout << x << ' ' ;
        std::cout << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
