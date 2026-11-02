// C++98 — цикл for.
#include "../../common/console.hpp"
#include <iostream>

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
