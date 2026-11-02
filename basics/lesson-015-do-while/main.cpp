// C++98 — цикл do / while.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

// Цикл do while

int main()
{
    console::setupConsoleEncoding();

    int a = 19;

    // do-while (хотя бы один раз цикл выполнится)
    do
    {
        cout << "Переменная a = " << a << endl;
        a++;
    } while (a < 20);

    /*
    // while
    while (a < 20)
    {
        cout << "Переменная a = " << a << endl;
        a++;
    }
    */

    return 0;
}
