// C++23 — std::bind_back и std::invoke_r; C++20 — std::bind_front.
#include <exception>
#include <functional>
#include <iostream>

#include "../../../basics/additions/common/check.hpp"

int subtract(int a, int b) { return a - b; }
void add_to(int& target, int x) { target += x; }

int main()
{
    try
    {
        auto minus_three = std::bind_back(subtract, 3);
        auto from_three = std::bind_front(subtract, 3);
        check(std::invoke_r<double>(minus_three, 10) == 7.0 && from_three(10) == -7, "argument order");
        int count = 0;
        auto add = std::bind_front(add_to, std::ref(count));
        add(4);
        check(count == 4, "reference binding");
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
