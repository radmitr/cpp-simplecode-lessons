// C++23 — if consteval; C++20 — consteval; C++11 — constexpr.
#include <exception>
#include <iostream>

#include "../../../basics/bonus/common/check.hpp"

consteval int compile_only(int x) { return x * 10; }
constexpr int choose(int x)
{
    if consteval { return compile_only(x); }
    else { return x; }
}

int main()
{
    try
    {
        constexpr int a = choose(2);
        static_assert(a == 20);
        volatile int input = 2;
        const int b = choose(input);
        check(b == 2, "runtime branch");
        std::cout << a << ' ' << b << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
