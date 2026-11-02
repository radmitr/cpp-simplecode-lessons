// C++98 — объявления и определения в нескольких файлах.
#pragma once

#include <iostream>

namespace myNamespace
{
    class MyClass
    {
    public:
        MyClass();
        ~MyClass();
        void printMessage(const char str[]);
        void myMethod();
        int getValue() const;
    };
}
