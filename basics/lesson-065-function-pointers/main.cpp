#include <iostream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

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
    setupConsoleEncoding();

    void(*fooPointer)();

    fooPointer = foo2;
    fooPointer();

    return 0;
}
