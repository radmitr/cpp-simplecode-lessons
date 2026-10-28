#include <iostream>
#include <functional>

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

void foo()
{
    cout << "foo()" << endl;
}

void bar()
{
    cout << "bar()" << endl;
}

int sum(int a, int b)
{
    return a + b;
}

int main(void)
{
    setupConsoleEncoding();

    function<void()> f;
    f = foo;
    f();

    f = bar;
    f();

    function<int(int, int)> f2;
    f2 = sum;
    int result = f2(2, 3);
    cout << "result=" << result << endl;

    return 0;
}
