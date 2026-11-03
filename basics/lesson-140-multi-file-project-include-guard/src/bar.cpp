// C++98 — защита заголовков от повторного включения.
#include "bar.h"

#include <iostream>

void bar()
{
    std::cout << "Вызвали bar()" << std::endl;
    foo2();
}

void bar2()
{
    std::cout << "Вызвали bar2()" << std::endl;
}
