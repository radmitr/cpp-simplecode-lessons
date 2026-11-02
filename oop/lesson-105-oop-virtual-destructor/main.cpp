// C++98 — виртуальные деструкторы; C++11 — override.
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
    console::setupConsoleEncoding();

    //B b;

    //B* bptr = new B();
    A* bptr = new B();
    delete bptr;

    return 0;
}
