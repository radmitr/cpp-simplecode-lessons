// C++26 — индексирование пакета типов и выражений.
#include <cstddef>
#include <exception>
#include <iostream>
#include <type_traits>

#include "../../../basics/bonus/common/check.hpp"

template<std::size_t I, class... T> requires (I < sizeof...(T))
using nth_type = T...[I];
template<std::size_t I, class... T> requires (I < sizeof...(T))
constexpr auto nth(T... values) { return values...[I]; }

int main()
{
    try
    {
        static_assert(std::is_same_v<nth_type<1, int, double, char>, double>);
        static_assert(nth<0>(10, 20, 30) == 10);
        static_assert(nth<2>(10, 20, 30) == 30);
        std::cout << nth<1>(10, 20, 30) << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
