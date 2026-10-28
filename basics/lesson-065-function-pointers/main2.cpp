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
    setupConsoleEncoding();

    int(*fooPointer)(int);

    fooPointer = foo2;
    cout << fooPointer(5) << endl;

    return 0;
}
