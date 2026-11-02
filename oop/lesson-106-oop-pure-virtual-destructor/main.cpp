// C++98 — чисто виртуальный деструктор с определением; C++11 — override.
#include <iostream>
#include <cstdlib>
#include <string>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

    A* bptr = new B();
    delete bptr;

    // A a; // object of abstract class type "A" is not allowed

    return 0;
}
