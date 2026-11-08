// C++20 — locate_zone, zoned_time, sys_time и local_time.
#include <chrono>
#include <exception>
#include <iostream>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        using namespace std::chrono;
        const auto* zone = locate_zone("America/New_York");
        const sys_seconds instant = sys_days{year{2024}/January/day{1}} + hours{12};
        const zoned_time<seconds> local(zone, instant);
        const local_seconds expected = local_days{year{2024}/January/day{1}} + hours{7};
        check(local.get_sys_time() == instant && local.get_local_time() == expected, "same instant in a zone");
        check(zone->get_info(instant).offset == -hours{5}, "winter offset");
        std::cout << "12:00 UTC -> 07:00 America/New_York\n";
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
