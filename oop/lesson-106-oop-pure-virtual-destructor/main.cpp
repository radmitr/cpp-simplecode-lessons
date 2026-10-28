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
        cout << "Конструктор A" << endl;
    }

    virtual ~A() = 0;
};

A::~A()
{
    cout << "Деструктор A" << endl;
}

class B : public A
{
public:
    B()
    {
        cout << "Конструктор B" << endl;
    }

    ~B() override
    {
        cout << "Деструктор B" << endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    A* bptr = new B();
    delete bptr;

    // A a; // object of abstract class type "A" is not allowed

    return 0;
}
