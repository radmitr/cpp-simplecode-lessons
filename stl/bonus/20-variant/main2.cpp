// C++17 — visit с двумя variant.
#include <exception>
#include <iostream>
#include <string>
#include <variant>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::variant<int, double> left = 3;
        std::variant<int, double> right = 2.5;
        const double sum = std::visit([](auto a, auto b) -> double { return a + b; }, left, right);
        check(sum == 5.5, "all combinations are callable");
        bool caught = false;
        try { (void)std::get<int>(right); }
        catch (const std::bad_variant_access&) { caught = true; }
        check(caught, "wrong alternative");
        std::cout << sum << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
