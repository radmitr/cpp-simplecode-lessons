// C++98 — указатели на функции.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int foo1(int a)
{
    return a - 1;
}

int foo2(int a)
{
    return a * 2;
}

int main(void)
{
    console::setupConsoleEncoding();

    int(*fooPointer)(int);

    fooPointer = foo2;
    cout << fooPointer(5) << endl;

    return 0;
}
