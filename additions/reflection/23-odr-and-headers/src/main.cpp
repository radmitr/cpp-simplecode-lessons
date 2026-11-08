// C++26 — статическая рефлексия через общий заголовок (экспериментально, GCC).
#include <exception>
#include <iostream>

#include "shared.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        check(count_from_other_translation_unit() == 2 && public_field_count<Shared>() == 2, "header metadata failed");
        std::cout << "fields=" << public_field_count<Shared>() << '\n';
        std::cout << "OK 23-odr-and-headers\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
