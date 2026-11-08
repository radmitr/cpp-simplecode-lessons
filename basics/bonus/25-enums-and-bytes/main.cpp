// C++23 — std::to_underlying, std::is_scoped_enum_v и std::byteswap.
#include <bit>
#include <cstdint>
#include <exception>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <utility>

#include "../../../basics/bonus/common/check.hpp"

enum class Permission : unsigned { read = 1, write = 4 };
enum Legacy { old_value };

int main()
{
    try
    {
        static_assert(std::is_scoped_enum_v<Permission>);
        static_assert(!std::is_scoped_enum_v<Legacy>);
        static_assert(std::is_same_v<decltype(std::to_underlying(Permission::write)), unsigned>);
        constexpr auto reversed = std::byteswap(std::uint32_t{0x01020304});
        static_assert(reversed == 0x04030201);
        static_assert(std::byteswap(reversed) == 0x01020304);
        std::cout << std::to_underlying(Permission::write) << ' ' << std::hex << reversed << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
