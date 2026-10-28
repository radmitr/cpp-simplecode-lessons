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
        cout << "Вызвался конструктор класса A" << endl;
    }

    ~A()
    {
        cout << "Вызвался деструктор класса A" << endl;;
    }
};

class B : private A
{
public:
    B()
    {
        cout << "Вызвался конструктор класса B" << endl;
    }

    ~B()
    {
        cout << "Вызвался деструктор класса B" << endl;;
    }
};

class C : private B
{
public:
    C()
    {
        cout << "Вызвался конструктор класса C" << endl;
    }

    ~C()
    {
        cout << "Вызвался деструктор класса C" << endl;;
    }
};

int main(void)
{
    setupConsoleEncoding();

    C c;
    cout << endl;

    return 0;
}
