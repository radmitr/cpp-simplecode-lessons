// C++20 — floor<days> и hh_mm_ss; C++14 — литералы chrono.
#include <chrono>
#include <exception>
#include <iostream>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        using namespace std::chrono;
        const sys_seconds before_epoch{seconds{-1}};
        const auto day_start = floor<days>(before_epoch);
        const hh_mm_ss time{before_epoch - day_start};
        check(day_start.time_since_epoch() == days{-1}, "floor for negative instant");
        check(time.hours() == 23h && time.minutes() == 59min && time.seconds() == 59s, "time since midnight");
        check(year_month_day{day_start} == year{1969}/December/day{31}, "previous calendar day");
        std::cout << time.hours().count() << ':' << time.minutes().count() << ':' << time.seconds().count() << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
