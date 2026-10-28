#include <iostream>
#include <cstdlib>
#include <string>

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

class A
{
public:
    A()
    {
        cout << "Вызвался конструктор A" << endl;
    }
};

class B : private A
{
public:
    B()
    {
        cout << "Вызвался конструктор B" << endl;
    }
};

class C : private B
{
public:
    C()
    {
        cout << "Вызвался конструктор C" << endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    C c;

    return 0;
}
