#include "MyClass.h"

namespace myNamespace
{
    MyClass::MyClass()
    {
    }

    MyClass::~MyClass()
    {
    }

    void MyClass::printMessage(char str[])
    {
        std::cout << str << std::endl;
    }

    void MyClass::myMethod()
    {
    }

    int MyClass::getValue() const
    {
        return 0;
    }
}
