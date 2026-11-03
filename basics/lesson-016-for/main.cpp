// C++98 — цикл for.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

// Цикл for

int main()
{
    console::setupConsoleEncoding();

    for (int i = 2; i < 13; i++)
    {
        cout << " Переменная i = " << i << endl;
    }

    return 0;
}
