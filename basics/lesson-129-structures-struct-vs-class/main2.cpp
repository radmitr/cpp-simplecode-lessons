#include <iostream>
#include <string>

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
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
