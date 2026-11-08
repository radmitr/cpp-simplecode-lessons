// C++11 — пользовательские числовые литералы и constexpr.
#include <exception>
#include <iostream>
#include <limits>
#include <stdexcept>

#include "../../../basics/bonus/common/check.hpp"

namespace units
{
    struct Length { unsigned long long millimetres; };
    constexpr Length operator""_mm(unsigned long long value) { return Length{value}; }
    constexpr Length operator""_m(unsigned long long value)
    {
        return value <= std::numeric_limits<unsigned long long>::max() / 1000
            ? Length{value * 1000} : throw std::out_of_range("length literal overflow");
    }
}

int main()
{
    try
    {
        using namespace units;
        constexpr auto distance = 2_m;
        constexpr auto gap = 7_mm;
        static_assert(distance.millimetres == 2000 && gap.millimetres == 7, "length units");
        bool rejected = false;
        try { (void)operator""_m(std::numeric_limits<unsigned long long>::max()); }
        catch (const std::out_of_range&) { rejected = true; }
        check(rejected, "overflow is rejected before multiplication");
        std::cout << distance.millimetres + gap.millimetres << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
