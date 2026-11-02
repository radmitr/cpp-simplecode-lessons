// C++98 — конструктор копирования.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

class MyClass
{
public:
    int data;

    MyClass(int data)
    {
        this->data = data;
        cout << "Constructor called " << this << endl;
    }

    ~MyClass()
    {
        cout << "Destructor called " << this << endl;
    }
};

int main(void)
{
    console::setupConsoleEncoding();

    MyClass a(1);
    MyClass b(a);

    return 0;
}
