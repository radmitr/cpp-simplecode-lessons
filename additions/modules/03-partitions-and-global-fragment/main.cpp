// C++20 — импорт первичного интерфейса с разделами.
#include <exception>
#include <iostream>

import geometry;

int main()
{
    try
    {
        Rectangle rectangle{3, 4};
        if (area(rectangle) != 12 || border(rectangle) != 14) return 1;
        std::cout << "12 14\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
