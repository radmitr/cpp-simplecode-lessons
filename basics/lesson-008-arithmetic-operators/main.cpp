// C++98 — арифметические операторы и приоритет операций.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*
 * ОПЕРАТОРЫ:
 *  - унарные
 *  - бинарные
 */

int main()
{
    console::setupConsoleEncoding();

    // УНАРНЫЕ
    int x = 5;
    cout << x << endl;

    x = -x;
    cout << x << endl;

    // БИНАРНЫЕ
    int a = 5, b = 2, c;
    c = a + b;

    cout << c << endl;
    cout << a * b << endl;

    // приоритет
    c = 2 + 2 * 2;
    cout << c << endl;

    c = (2 + 2) * 2;
    cout << c << endl;

    return 0;
}
