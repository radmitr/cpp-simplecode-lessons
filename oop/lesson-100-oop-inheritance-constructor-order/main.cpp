// C++98 — порядок вызова конструкторов при наследовании.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

    C c;

    return 0;
}
