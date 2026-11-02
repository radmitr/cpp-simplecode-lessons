// C++98 — указатели на функции.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

void foo1()
{
    cout << "void foo1()" << endl;
}

void foo2()
{
    cout << "void foo2()" << endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    void(*fooPointer)();

    fooPointer = foo2;
    fooPointer();

    return 0;
}
