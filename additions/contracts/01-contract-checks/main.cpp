// C++26 — контракты pre, post и contract_assert (GCC: -fcontracts).
#include <exception>
#include <iostream>
#include <limits>

#include "../../../basics/additions/common/check.hpp"

int twice(const int x)
    pre(x > 0 && x <= std::numeric_limits<int>::max() / 2)
    post(result: result > x)
{
    contract_assert(x > 0);
    return x * 2;
}

int main()
{
    try
    {
        check(twice(3) == 6 && twice(1) == 2, "valid contracts");
        std::cout << twice(3) << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
