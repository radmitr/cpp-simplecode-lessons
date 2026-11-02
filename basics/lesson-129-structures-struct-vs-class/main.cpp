// C++98 — struct, class и доступ к членам.
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

    MyClass mc;
    MyStruct ms;

    //cout << ms.a << endl;
    ms.print();

    return 0;
}
