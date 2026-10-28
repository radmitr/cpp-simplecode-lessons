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
        cout << "выделена динамическая память, объект класса A" << endl;
    }

    virtual ~A()
    {
        cout << "освобождена динамическая память, объект класса A" << endl;
    }
};

class B : public A
{
public:
    B()
    {
        cout << "выделена динамическая память, объект класса B" << endl;
    }

    ~B() override
    {
        cout << "освобождена динамическая память, объект класса B" << endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    //B b;

    //B* bptr = new B();
    A* bptr = new B();
    delete bptr;

    return 0;
}
