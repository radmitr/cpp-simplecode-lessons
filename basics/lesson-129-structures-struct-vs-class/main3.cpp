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

class MyClass2 : public MyClass
{
};

struct MyStruct
{
    int a = 55;
};

struct MyStruct2 : MyStruct
{
};

int main(void)
{
    setupConsoleEncoding();

    MyClass2 mc2;
    MyStruct2 ms2;

    cout << mc2.a << endl;
    cout << ms2.a << endl;

    return 0;
}
