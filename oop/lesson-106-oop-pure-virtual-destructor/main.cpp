#include <iostream>
#include <cstdlib>
#include <clocale>
#include <string>

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
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
