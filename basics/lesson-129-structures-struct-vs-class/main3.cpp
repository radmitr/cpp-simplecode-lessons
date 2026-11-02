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
    console::setupConsoleEncoding();

    MyClass2 mc2;
    MyStruct2 ms2;

    cout << mc2.a << endl;
    cout << ms2.a << endl;

    return 0;
}
