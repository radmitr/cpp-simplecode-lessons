// C++98 — объявления и определения в нескольких файлах.
#include "MyClass.h"

#include <iostream>

namespace myNamespace
{
    MyClass::MyClass()
    {
    }

    MyClass::~MyClass()
    {
    }

    void MyClass::printMessage(const char str[])
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
