// C++26 — std::simd: загрузка и сохранение неполного блока.
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
        const std::array short_input{5, 7};
        using Vector = std::simd::vec<int, 4>;
        const auto block = std::simd::partial_load<Vector>(short_input);
        std::array<int, 3> output{-1, -1, -1};
        std::simd::partial_store(block, output);
        check(output == std::array{5, 7, 0}, "zero-filled tail and partial store");
        check(std::simd::any_of(block > 6) && !std::simd::all_of(block > 0), "partial mask");
        std::cout << output[0] << ' ' << output[1] << ' ' << output[2] << '\n';
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
