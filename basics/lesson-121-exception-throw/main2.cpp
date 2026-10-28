#include <iostream>
#include <fstream>

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

void foo(int value)
{
    if (value < 0)
    {
        throw value;
    }
    cout << "value = " << value << endl;
}

int main(void)
{
    setupConsoleEncoding();

    try
    {
        foo(-55);
    }
    catch(const int e)
    {
        cerr << "Мы поймали: " << e << '\n';
    }

    return 0;
}
