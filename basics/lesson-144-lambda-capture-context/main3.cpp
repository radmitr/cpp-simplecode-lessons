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

int main(void)
{
    setupConsoleEncoding();

    auto f = []()->int {
        return 1.45;
    };

    f();

    function<float()> f2 = []() {
        return 1.45;
    };

    f2();

    function<float()> f3 = []()->int {
        return 1.45;
    };

    f3();

    return 0;
}
