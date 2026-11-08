// C++20 — импорт пользовательского заголовка как header unit.
#include <exception>
#include <iostream>

import "settings.hpp";

int main()
{
    try
    {
        static_assert(DEMO_FACTOR == 3);
        if (scaled(7) != 21) return 1;
        std::cout << "21\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
