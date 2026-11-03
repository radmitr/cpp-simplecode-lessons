// C++98 — переход к следующей итерации через continue.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/* Ключевое слово continue */

int main()
{
    console::setupConsoleEncoding();

    for (int i = 0; i < 5; i++)
    {
        if (i == 2)
        {
            continue;
        }
        cout << "переменная i: " << i << endl;
    }

    return 0;
}
