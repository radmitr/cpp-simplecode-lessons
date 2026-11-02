// C++98 — цикл while.
#include "../../common/console.hpp"
#include <iostream>

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
