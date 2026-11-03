// C++11 — захваты лямбда-выражений; C++17 — вывод аргументов шаблона класса std::function.
#include <functional>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    int a = 55;
    int b = 10;

    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    function f = [a]() {
        cout << a << " " << &a << endl;
    };

    function f2 = [&a, b]() mutable {
        cout << a << " " << &a << endl;
        a = 1323;
        cout << b << " " << &b << endl;
        b = 11;
    };

    function f3 = [=]() mutable {
        cout << a << " " << &a << endl;
        a = 1324;
        cout << b << " " << &b << endl;
        b = 12;
    };

    function f4 = [&]() {
        cout << a << " " << &a << endl;
        a = 1325;
        cout << b << " " << &b << endl;
        b = 13;
    };

    f();
    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    f2();
    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    f3();
    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    f4();
    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    return 0;
}
