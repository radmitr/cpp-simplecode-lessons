// C++23 — [[assume]] и std::unreachable.
#include <exception>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "../../../basics/additions/common/check.hpp"

enum class Choice { first, second };
int rank(Choice c)
{
    switch (c) { case Choice::first: return 1; case Choice::second: return 2; }
    std::unreachable();
}
int half_positive(int x)
{
    if (x <= 0) throw std::invalid_argument("positive number required");
    [[assume(x > 0)]];
    return x / 2;
}

int main()
{
    try
    {
        check(half_positive(10) == 5 && rank(Choice::second) == 2, "valid path");
        bool rejected = false;
        try { (void)half_positive(0); }
        catch (const std::invalid_argument&) { rejected = true; }
        check(rejected, "input validation");
        std::cout << 5 << ' ' << 2 << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
