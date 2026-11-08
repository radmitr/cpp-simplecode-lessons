// C++26 — директива #embed и параметры ресурса.
#include <exception>
#include <iostream>
#include <iterator>

#include "../../../basics/bonus/common/check.hpp"

constexpr unsigned char full[] = {
#embed "sample.bin"
};
constexpr unsigned char framed[] = {
#embed "sample.bin" limit(2) prefix(0,) suffix(,255)
};
constexpr unsigned char empty[] = {
#embed "empty.bin" if_empty(7)
};

int main()
{
    try
    {
        static_assert(std::size(full) == 4 && full[0] == 65 && full[3] == 0);
        static_assert(std::size(framed) == 4 && framed[0] == 0 && framed[3] == 255);
        static_assert(std::size(empty) == 1 && empty[0] == 7);
        std::cout << std::size(full) << ' ' << int(full[3]) << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
