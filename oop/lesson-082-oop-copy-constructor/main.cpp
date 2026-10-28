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

int main(void)
{
    setupConsoleEncoding();

    MyClass a(1);
    foo(a);

    return 0;
}
