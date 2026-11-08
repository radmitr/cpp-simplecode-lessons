// C++23 — std::move_only_function; C++14 — захват unique_ptr перемещением.
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <utility>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::move_only_function<int(int)> task = [p = std::make_unique<int>(7)](int x) { return *p + x; };
        auto moved = std::move(task);
        check(!task && moved && moved(5) == 12, "move-only ownership");
        std::move_only_function<int() noexcept> safe = []() noexcept { return 3; };
        static_assert(noexcept(safe()));
        check(safe() == 3, "noexcept signature");
        std::cout << moved(5) << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
