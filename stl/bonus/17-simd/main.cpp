// C++26 — std::simd::vec, маски и поэлементная арифметика.
#include <array>
#include <exception>
#include <iostream>
#include <version>

#if __has_include(<simd>)
#include <simd>
#endif
#if defined(__cpp_lib_simd) || (defined(__GLIBCXX__) && defined(__glibcxx_simd))

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        const std::array input{1, 2, 3, 4};
        using Vector = std::simd::vec<int, 4>;
        const auto values = std::simd::unchecked_load<Vector>(input);
        const auto doubled = values * 2;
        std::array<int, 4> output{};
        std::simd::unchecked_store(doubled, output);
        check(output == std::array{2, 4, 6, 8}, "vector arithmetic");
        check(std::simd::all_of(doubled > 0), "mask");
        check(std::simd::reduce(doubled) == 20, "reduction");
        std::cout << std::simd::reduce(doubled) << '\n';
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
    std::cout << "UNAVAILABLE: stl/bonus/17-simd\n";
    return 77;
}
#endif
