// C++11 — свойства типов из <type_traits>; C++17 — if constexpr и std::string_view.
#include <exception>
#include <iostream>
#include <string_view>
#include <type_traits>

#include "../../../basics/bonus/common/check.hpp"

template<class T> std::string_view describe(const T&)
{
    if constexpr (std::is_integral_v<T>) return "integer";
    else return "other";
}
template<class T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
T twice(T value) { return value * 2; }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(std::is_integral_v<int> && !std::is_integral_v<double>);
        static_assert(std::is_same_v<std::remove_reference_t<int&>, int>);
        check(describe(7) == "integer" && describe(2.5) == "other", "compile-time branch failed");
        check(twice(4) == 8, "enable_if constraint failed");
        std::cout << describe(7) << ' ' << describe(2.5) << '\n';
        std::cout << "OK 18-traits-if-constexpr\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
