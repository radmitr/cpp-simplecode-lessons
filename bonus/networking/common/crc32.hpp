#ifndef NETWORKING_CRC32_HPP
#define NETWORKING_CRC32_HPP

#include <cstdint>
#include <string_view>

namespace transfer
{
// CRC-32/ISO-HDLC. Проверка случайного повреждения, не криптографическая защита.
inline std::uint32_t updateCrc(std::uint32_t state, std::string_view bytes)
{
    for (unsigned char byte : bytes)
    {
        state ^= byte;
        for (int bit = 0; bit < 8; ++bit)
            state = (state >> 1) ^ ((state & 1) ? 0xedb88320u : 0u);
    }
    return state;
}

inline std::uint32_t crc32(std::string_view bytes)
{
    return updateCrc(0xffffffffu, bytes) ^ 0xffffffffu;
}
} // namespace transfer
#endif
