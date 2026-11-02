// C++98 — возврат нескольких результатов через ссылки.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/*
    Возврат нескольких значений функции через ссылки.
*/

// параметры - ссылки
void foo(int& a, int& b, int& c)
{
    a = 10;
    b *= 2;
    c -= 100;
}

int main()
{
    console::setupConsoleEncoding();

    int a = 0, b = 4, c = 34;
    cout << " Start: a = " << a << endl;
    cout << " Satrt: b = " << b << endl;
    cout << " Start: c = " << c << endl << endl;

    foo(a, b, c);
    cout << " foo: a = " << a << endl;
    cout << " foo: b = " << b << endl;
    cout << " foo: c = " << c << endl << endl;

    return 0;
}
