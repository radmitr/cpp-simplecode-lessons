// C++20 — import интерфейса и экспортируемый шаблон.
#include <exception>
#include <iostream>

import facade;

int main()
{
    try
    {
        if (square(5) != 25 || twice(3) != 6) return 1;
        std::cout << "25 6\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
