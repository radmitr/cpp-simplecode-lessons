// C++20 — неоднозначное и несуществующее местное время.
#include <chrono>
#include <exception>
#include <iostream>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        using namespace std::chrono;
        const auto* zone = locate_zone("America/New_York");
        const auto gap = local_days{year{2024}/March/day{10}} + hours{2} + minutes{30};
        check(zone->get_info(gap).result == local_info::nonexistent, "spring gap");
        bool nonexistent = false;
        try { (void)zone->to_sys(gap); }
        catch (const nonexistent_local_time&) { nonexistent = true; }
        const auto repeated = local_days{year{2024}/November/day{3}} + hours{1} + minutes{30};
        check(zone->get_info(repeated).result == local_info::ambiguous, "autumn overlap");
        bool ambiguous = false;
        try { (void)zone->to_sys(repeated); }
        catch (const ambiguous_local_time&) { ambiguous = true; }
        const auto early = zone->to_sys(repeated, choose::earliest);
        const auto late = zone->to_sys(repeated, choose::latest);
        check(nonexistent && ambiguous && late - early == hours{1}, "explicit ambiguity choice");
        std::cout << duration_cast<minutes>(late - early).count() << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
