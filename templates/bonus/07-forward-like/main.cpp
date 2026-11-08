// C++23 — std::forward_like.
#include <exception>
#include <iostream>
#include <type_traits>
#include <utility>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        int value = 7;
        static_assert(std::is_same_v<decltype(std::forward_like<int&>(value)), int&>);
        static_assert(std::is_same_v<decltype(std::forward_like<const int&>(value)), const int&>);
        static_assert(std::is_same_v<decltype(std::forward_like<int>(value)), int&&>);
        static_assert(std::is_same_v<decltype(std::forward_like<const int>(value)), const int&&>);
        std::forward_like<int&>(value) = 8;
        check(value == 8, "reference identity");
        std::cout << value << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
