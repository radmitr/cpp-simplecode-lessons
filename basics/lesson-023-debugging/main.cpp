// C++98 — вызовы функций и локальные переменные.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int Sum(int a, int b)
{
    int c = a + b;
    return c;
}

/*-------------------------
 *     О Т Л А Д К А
 --------------------------*/

int main()
{
    console::setupConsoleEncoding();

    int a = 5;
    int b = 6;
    int c;

    c = a + b;
    c = Sum(a, b);

    cout << "Hello World! " << endl;
    cout << "Result: ";
    cout << c << endl;
    return 0;
}
