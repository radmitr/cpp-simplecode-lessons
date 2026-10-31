#include <vector>
#include <type_traits>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        std::vector<int> values{1, 2};
        auto copy = values[0];
        auto& reference = values[0];
        copy = 9; reference = 7;
        check(copy == 9 && values[0] == 7, "copy/reference mismatch");
        int value = 5;
        static_assert(std::is_same_v<decltype(value), int>);
        static_assert(std::is_same_v<decltype((value)), int&>);
        decltype(auto) result = (value);
        result = 10;
        check(value == 10, "decltype(auto) lost reference");
        std::cout << value << ' ' << values[0] << '\n';
        std::cout << "OK 06-auto-and-decltype\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
