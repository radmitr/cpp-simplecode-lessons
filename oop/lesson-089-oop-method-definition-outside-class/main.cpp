// C++98 — определение методов за пределами класса.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

class MyClass
{
private:

public:
    MyClass();
    ~MyClass();

    void printMessages();
};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

void MyClass::printMessages()
{
    cout << "Hello!" << endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    MyClass a;
    a.printMessages();

    return 0;
}
