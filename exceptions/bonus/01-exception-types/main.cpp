// C++98 — семейства std::logic_error и std::runtime_error.
#include <iostream>
#include <stdexcept>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    int caught = 0;
    try { throw std::invalid_argument("age must not be negative"); }
    catch (const std::logic_error& error)
    {
        ++caught; // invalid_argument наследует logic_error.
        std::cout << "logic_error: " << error.what() << '\n';
    }
    try { throw std::overflow_error("result does not fit"); }
    catch (const std::runtime_error& error)
    {
        ++caught; // overflow_error наследует runtime_error.
        std::cout << "runtime_error: " << error.what() << '\n';
    }
    check(caught == 2, "wrong exception hierarchy");
    std::cout << "OK exception-families\n";
}
