// C++23 — std::ranges::elements_of и std::generator; C++20 — корутины.
#include <exception>
#include <generator>
#include <iostream>
#include <ranges>
#include <stdexcept>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

std::generator<int> inner() { co_yield 1; co_yield 2; }
std::generator<int> outer()
{
    co_yield 0;
    co_yield std::ranges::elements_of(inner());
    throw std::runtime_error("sequence error");
}

int main()
{
    try
    {
        std::vector<int> values;
        bool caught = false;
        try { for (int x : outer()) values.push_back(x); }
        catch (const std::runtime_error&) { caught = true; }
        check(caught && values == std::vector{0, 1, 2}, "nested yields and exception");
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
