#include <bit>
#include <cstdint>
#include <array>
#include <cstddef>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        const std::uint32_t flags = 0b0101;
        check((flags & 0b0001u) != 0 && (flags & 0b0010u) == 0, "bit mask failed");
        const auto bytes = std::bit_cast<std::array<std::byte, sizeof(std::uint32_t)>>(flags);
        const auto restored = std::bit_cast<std::uint32_t>(bytes);
        check(restored == flags, "bit_cast round trip failed");
        std::cout << "native endian: " << (std::endian::native == std::endian::little ? "little" : "other") << '\n';
        std::cout << "OK 26-bits-and-representation\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
