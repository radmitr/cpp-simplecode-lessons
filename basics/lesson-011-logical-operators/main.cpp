// C++98 — сравнения, логические операторы и сокращённое вычисление.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/*-----------------------------------------
    Операторы сравнения:
    >   -  больше
    <   -  меньше
    >=  -  больше/равно
    <=  -  меньше/равно

    Операторы равенства:
    ==  - равно
    !=  - не равно

    Логические операторы:
    &&  - и
    ||  - или
    !   - не
------------------------------------------*/

int main()
{
    console::setupConsoleEncoding();

    int a = 3;
    int b = 3;
    int c = 4;

    cout << (4 > 5) << endl;
    cout << (5 == 5) << endl;
    cout << (5 != 5) << endl;
    cout << (a == b) << endl;
    cout << (a == c) << endl;
    cout << (a == b) << endl;

    cout << !(a == b) << endl;  // инверсия
    cout << !(a != b) << endl;

    cout << ((a == b) && (5 > 4) && (1 == 1)) << endl;
    cout << ((3 == 3) || (1 > 0)) << endl;

    //=== etc... ===

    return 0;
}
