// C++14 — шаблоны переменных, integer_sequence и index_sequence.
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
#include <type_traits>
#include <utility>

#include "../../../basics/bonus/common/check.hpp"

template<class T> constexpr T pi = T(3.1415926535897932385L);
template<class T> constexpr bool pointer_v = std::is_pointer<T>::value;
template<std::size_t... I>
constexpr std::array<std::size_t, sizeof...(I)> indices(std::index_sequence<I...>)
{
    return {{I...}};
}

int main()
{
    try
    {
        static_assert(pointer_v<int*> && !pointer_v<int>, "variable template");
        constexpr auto order = indices(std::make_index_sequence<4>{});
        static_assert(order.size() == 4 && order[3] == 3, "generated index pack");
        check(pi<double> > 3.14 && pi<double> < 3.15, "typed constant");
        std::cout << order.size() << ' ' << order[0] << ' ' << order[3] << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
