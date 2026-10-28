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
    int a = 5;
};

class MyClass2 : MyClass
{
};

struct MyStruct
{
    int a = 55;
};

int main(void)
{
    setupConsoleEncoding();

    MyClass mc;
    MyClass2 mc2;
    MyStruct ms;

    cout << mc.a << endl;
    //cout << mc2.a << endl; // member "MyClass::a" (declared at line 21) is inaccessible

    return 0;
}
