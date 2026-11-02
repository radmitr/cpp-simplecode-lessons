// C++98 — выход из цикла через break.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/* Ключевое слово break */

int main()
{
    console::setupConsoleEncoding();

    cout << "Начало цикла for" << endl;
    for (int i = 0; ; i++)
    {
        cout << " переменная i = " << i << endl;
        if (i == 5)
        {
            cout << " === BREAK === " << endl;
            break;
        }
    }
    cout << "Конец цикла for\n" << endl;

    int i = 0;
    cout << "Начало цикла while" << endl;
    while (true)
    {
        cout << " переменная i = " << i << endl;
        i++;
        if (i == 5)
        {
            cout << " === BREAK === " << endl;
            break;
        }
    }
    cout << "Конец цикла while" << endl;

    return 0;
}
