// C++20 — import именованного модуля.
#include <exception>
#include <iostream>

#include "../../../basics/additions/common/check.hpp"

import arithmetic;

int main()
{
    try
    {
        check(add(2, 3) == 5 && total(Pair{7, 9}) == 16, "exported interface");
        std::cout << add(2, 3) << ' ' << total(Pair{7, 9}) << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
