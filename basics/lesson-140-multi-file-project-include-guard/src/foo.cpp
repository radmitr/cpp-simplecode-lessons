// C++98 — защита заголовков от повторного включения.
#include "foo.h"

#include <iostream>

void foo()
{
    std::cout << "Вызвали foo()" << std::endl;
    bar2();
}

void foo2()
{
    std::cout << "Вызвали foo2()" << std::endl;
}
