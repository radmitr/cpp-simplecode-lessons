// C++23 — явный параметр объекта рекурсивной лямбды.
#include <exception>
#include <iostream>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        const auto factorial = [](this auto self, int n) -> int {
            return n <= 1 ? 1 : n * self(n - 1);
        };
        check(factorial(0) == 1 && factorial(5) == 120, "recursive lambda");
        std::cout << factorial(5) << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
