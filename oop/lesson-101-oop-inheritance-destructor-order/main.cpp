// C++98 — порядок вызова деструкторов при наследовании.
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
    console::setupConsoleEncoding();

    C c;
    cout << endl;

    return 0;
}
