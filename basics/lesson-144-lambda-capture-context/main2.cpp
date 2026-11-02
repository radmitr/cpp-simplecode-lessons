// C++11 — захваты лямбда-выражений.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

class MyClass
{
public:
    int a = 11;

    void msg()
    {
        cout << "msg" << endl;
    }

    void lambda()
    {
        auto f = [this]() {
            this->msg();
        };
        f();
    }
};

int main(void)
{
    console::setupConsoleEncoding();

    MyClass m;

    m.lambda();

    return 0;
}
