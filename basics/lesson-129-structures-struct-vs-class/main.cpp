#include <iostream>
#include <string>

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
    void print()
    {
        cout << a << endl;
    }

private:
    int a = 5;
};

struct MyStruct
{
public:
    MyStruct()
    {

    }

    MyStruct(int a)
    {
        this->a = a;
    }

    ~MyStruct()
    {

    }

    void print()
    {
        cout << a << endl;
    }

private:
    int a = 55;
};

int main(void)
{
    setupConsoleEncoding();

    MyClass mc;
    MyStruct ms;

    //cout << ms.a << endl;
    ms.print();

    return 0;
}
