// C++98 — варианты записи цикла for.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

// Цикл for

int main()
{
    console::setupConsoleEncoding();

    int i = 0;

    cout << " 1-й цикл: " << endl;
    for (; i < 10; i++)
    {
        cout << "Переменная i: " << i << endl;
    }

    cout << "--------------------\n";
    cout << " 2-й цикл: " << endl;

    for (; i < 20; i++)
    {
        cout << "Переменная i: " << i << endl;
    }

    cout << "--------------------\n";
    cout << " 3-й цикл: " << endl;

    for (i = 0; i < 10;)
    {
        cout << "Переменная i: " << i << endl;
        i++;
    }

    cout << "--------------------\n";
    cout << " 4-й цикл: " << endl;

    /*
    for (;;)
    {
        cout << "Бесконечный цикл" << endl;
    }
    */

    for (int i = 0, j = 10; i < 10 && j != 5; i++, j--)
    {
        cout << "Переменная i = " << i << endl;
        cout << " Переменная j = " << j << endl;
    }

    return 0;
}
