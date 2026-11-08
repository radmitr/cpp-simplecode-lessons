// C++26 — std::optional<T&> и optional как диапазон.
#include <exception>
#include <iostream>
#include <optional>
#include <ranges>
#include <version>

#if defined(__cpp_lib_optional) && __cpp_lib_optional >= 202506L && defined(__cpp_lib_optional_range_support)

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        int a = 1, b = 2;
        std::optional<int&> reference(a);
        reference.value() = 7;
        check(a == 7, "write through reference");
        reference.emplace(b);
        reference.value() = 9;
        check(a == 7 && b == 9, "rebind");
        reference.reset();
        check(!reference && b == 9, "no ownership");
        std::optional<int> value = 3;
        int sum = 0;
        for (int x : value | std::views::transform([](int x) { return x * 2; })) sum += x;
        check(sum == 6, "optional range");
        value.reset();
        check(std::ranges::distance(value) == 0, "empty range");
        std::cout << a << ' ' << b << ' ' << sum << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
#else
int main()
{
    std::cout << "UNAVAILABLE: stl/bonus/15-optional-reference\n";
    return 77;
}
#endif
