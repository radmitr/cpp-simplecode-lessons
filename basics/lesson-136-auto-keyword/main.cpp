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

int main(void)
{
    setupConsoleEncoding();

    auto a = 10;
    auto b = 1.44;
    auto c = "string";
    auto d = true;
    //auto e; // cannot deduce 'auto' type (initializer required)

    cout << "a = " << a << ", sizeof(a) = " << sizeof(a) << endl;
    cout << "b = " << b << ", sizeof(b) = " << sizeof(b) << endl;
    cout << "c = " << c << ", sizeof(c) = " << sizeof(c) << endl;
    cout << "d = " << d << ", sizeof(d) = " << sizeof(d) << endl;

    return 0;
}
