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

union MyUnion
{
    short int a;
    int b;
    float c;
};

void printMyUnion(MyUnion u)
{
    cout << "a = " << u.a << endl;
    cout << "b = " << u.b << endl;
    cout << "c = " << u.c << endl;
}

int main(void)
{
    setupConsoleEncoding();

    MyUnion u;

    u.a = 5;
    printMyUnion(u);
    cout << endl;

    u.b = 175000;
    printMyUnion(u);
    cout << endl;

    u.c = 43.54;
    printMyUnion(u);
    cout << endl;

    return 0;
}
