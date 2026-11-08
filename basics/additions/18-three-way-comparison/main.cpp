// C++20 — operator<=>, default-сравнение и partial_ordering.
#include <compare>
#include <exception>
#include <iostream>
#include <limits>
#include <type_traits>

#include "../../../basics/additions/common/check.hpp"

struct Point
{
    int x;
    int y;
    auto operator<=>(const Point&) const = default;
};

int main()
{
    try
    {
        const Point first{1, 9};
        const Point second{2, 0};
        check(first < second && first != second && first == Point{1, 9}, "lexicographic default comparison");
        static_assert(std::is_same_v<decltype(first <=> second), std::strong_ordering>);
        const double nan = std::numeric_limits<double>::quiet_NaN();
        const auto result = nan <=> 1.0;
        static_assert(std::is_same_v<decltype(nan <=> 1.0), std::partial_ordering>);
        check(result == std::partial_ordering::unordered, "unordered is not equal");
        check(!(result < 0) && !(result == 0) && !(result > 0), "three comparisons can all be false");
        std::cout << (first < second) << ' ' << (result == std::partial_ordering::unordered) << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
