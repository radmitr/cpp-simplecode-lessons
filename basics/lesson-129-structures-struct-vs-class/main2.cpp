// C++98 — struct, class и доступ к членам.
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

    MyClass mc;
    MyClass2 mc2;
    MyStruct ms;

    cout << mc.a << endl;
    //cout << mc2.a << endl; // member "MyClass::a" (declared at line 21) is inaccessible

    return 0;
}
