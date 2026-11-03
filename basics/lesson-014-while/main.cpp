// C++98 — цикл while.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

// Цикл while

int main()
{
    console::setupConsoleEncoding();

    int a = 0;

    while (a < 10)
    {
        cout << " Переменная a = " << a++ << endl;
        // a++;
    }

    return 0;
}
