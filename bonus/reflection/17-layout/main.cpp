#include <cstddef>
#include "../common/reflection.hpp"

struct Layout { char tag; int value; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(std::meta::size_of(^^Layout) == sizeof(Layout));
        static_assert(std::meta::alignment_of(^^Layout) == alignof(Layout));
        static_assert(std::meta::offset_of(^^Layout::value).bytes == offsetof(Layout, value));
        std::cout << "size=" << std::meta::size_of(^^Layout)
                  << ", value offset=" << std::meta::offset_of(^^Layout::value).bytes << '\n';
        std::cout << "OK 17-layout\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
