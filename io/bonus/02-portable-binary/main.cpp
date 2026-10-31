#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

static_assert(std::numeric_limits<unsigned char>::digits == 8,
              "This file format requires 8-bit bytes");

struct Point
{
    std::uint32_t x;
    std::uint32_t y;
    std::uint32_t z;
};

using Bytes = std::array<unsigned char, 16>;

void encode(Bytes& bytes, std::size_t offset, std::uint32_t value)
{
    for (unsigned i = 0; i < 4; ++i)
    {
        bytes[offset + i] = static_cast<unsigned char>((value >> (8 * i)) & 0xffu);
    }
}

std::uint32_t decode(const Bytes& bytes, std::size_t offset)
{
    std::uint32_t value = 0;
    for (unsigned i = 0; i < 4; ++i)
    {
        value |= static_cast<std::uint32_t>(bytes[offset + i]) << (8 * i);
    }
    return value;
}

void save(const std::string& path, const Point& point)
{
    Bytes bytes{'P', 'T', '0', '1'};
    encode(bytes, 4, point.x);
    encode(bytes, 8, point.y);
    encode(bytes, 12, point.z);
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    if (!output.write(reinterpret_cast<const char*>(bytes.data()), bytes.size()))
    {
        throw std::runtime_error("Cannot write file");
    }
    output.close();
    if (!output)
    {
        throw std::runtime_error("Cannot close file");
    }
}

Point load(const std::string& path)
{
    Bytes bytes{};
    std::ifstream input(path, std::ios::binary);
    if (!input)
    {
        throw std::runtime_error("Cannot open file");
    }
    if (!input.read(reinterpret_cast<char*>(bytes.data()), bytes.size()))
    {
        throw std::runtime_error("Incomplete record");
    }
    if (bytes[0] != 'P' || bytes[1] != 'T' || bytes[2] != '0' || bytes[3] != '1')
    {
        throw std::runtime_error("Unknown file format");
    }
    char extra = 0;
    if (input.get(extra))
    {
        throw std::runtime_error("Unexpected trailing data");
    }
    if (!input.eof() || input.bad())
    {
        throw std::runtime_error("Cannot read file");
    }
    return {decode(bytes, 4), decode(bytes, 8), decode(bytes, 12)};
}

int main(int argc, char* argv[])
{
    const bool readOnly = argc == 3 && std::string(argv[1]) == "--read";
    if (argc != 1 && !readOnly)
    {
        std::cerr << "Usage: lesson [--read FILE]\n";
        return 1;
    }
    const std::string path = readOnly ? argv[2] : "point-v1.bin";
    try
    {
        if (!readOnly)
        {
            save(path, {487, 212, 946});
        }
        const Point point = load(path);
        std::cout << "Point(" << point.x << ", " << point.y << ", " << point.z << ")\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
