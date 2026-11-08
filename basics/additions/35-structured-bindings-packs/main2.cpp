// C++26 — структурированная привязка как условие.
#include <exception>
#include <iostream>

#include "../../../basics/additions/common/check.hpp"

struct Result
{
    int value;
    bool ok;
    explicit operator bool() const { return ok; }
};

int main()
{
    try
    {
        if (auto [value, ok] = Result{7, true})
        {
            check(ok && value == 7, "condition result");
            std::cout << value << '\n';
        }
        else { check(false, "success branch"); }
        if (auto [value, ok] = Result{0, false}) { check(value == 0 && ok, "unexpected success"); }
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
