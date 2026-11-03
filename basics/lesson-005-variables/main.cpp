// C++98 — объявление и изменение переменных.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

// тип_данных имя_переменной;

int main()
{
    console::setupConsoleEncoding();

    int a = 5;
    cout << "a = " << a << endl;

    a = 10;
    cout << "a = " << a << endl;

    int b = 1 , c = 2, Age = 10;
    cout << Age << " " << b << " " << c << endl;

    double n = 1.551;
    cout << n << endl;

    char s = 'f';
    cout << s << endl;

    bool f = true;
    cout << f << endl;  // 1

    f = false;
    cout << f << endl;  // 0

    return 0;
}
