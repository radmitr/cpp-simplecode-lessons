// C++20 — year_month_day, sys_days и календарная арифметика.
#include <chrono>
#include <exception>
#include <iostream>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        using namespace std::chrono;
        const year_month_day leap = year{2024}/February/day{29};
        check(leap.ok(), "valid leap date");
        const sys_days point(leap);
        check(year_month_day(point + days{1}) == year{2024}/March/day{1}, "next civil day");
        const auto invalid = leap + years{1};
        check(!invalid.ok(), "calendar arithmetic can produce invalid date");
        const year_month_day clamped{(leap.year() + years{1}) / leap.month() / last};
        check(clamped == year{2025}/February/day{28}, "explicit end-of-month choice");
        check(weekday{point}.iso_encoding() == 4, "Thursday");
        std::cout << int(clamped.year()) << '-' << unsigned(clamped.month()) << '-' << unsigned(clamped.day()) << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
