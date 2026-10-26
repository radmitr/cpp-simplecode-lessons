#pragma once

#include <iostream>

namespace myNamespace
{
    class MyClass
    {
    public:
        MyClass();
        ~MyClass();
        void printMessage(char str[]);
        void myMethod();
        int getValue() const;
    };

}
