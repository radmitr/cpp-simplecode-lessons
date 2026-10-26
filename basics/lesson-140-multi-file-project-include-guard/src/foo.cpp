#include "foo.h"

void foo()
{
    std::cout << "Вызвали foo()" << std::endl;
    bar2();
}

void foo2()
{
    std::cout << "Вызвали foo2()" << std::endl;
}
