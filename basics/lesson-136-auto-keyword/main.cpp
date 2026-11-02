// C++11 — вывод типа через auto.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    auto a = 10;
    auto b = 1.44;
    auto c = "string";
    auto d = true;
    //auto e; // cannot deduce 'auto' type (initializer required)

    cout << "a = " << a << ", sizeof(a) = " << sizeof(a) << endl;
    cout << "b = " << b << ", sizeof(b) = " << sizeof(b) << endl;
    cout << "c = " << c << ", sizeof(c) = " << sizeof(c) << endl;
    cout << "d = " << d << ", sizeof(d) = " << sizeof(d) << endl;

    return 0;
}
