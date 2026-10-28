#include <iostream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

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

void foo(MyClass value)
{
    cout << "Function FOO called" << endl;
}

MyClass foo2()
{
    cout << "Function FOO_2 called" << endl;
    MyClass temp(2);
    return temp;
}

int main(void)
{
    setupConsoleEncoding();

    // MyClass a(1);
    // foo(a);

    // только один вызов деструктора, потому что компилятор применил
    // оптимизацию возврата значения (RVO — Return Value Optimization)
    // чтобы отключить RVO - использовать флаг -fno-elide-constructors
    MyClass b = foo2();

    return 0;
}
