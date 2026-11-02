// C++98 — прототипы функций.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/* прототипы функций */

int foo(int a, int b);          // прототип функции (предварительное объявление)
void foo2();

// *** main ***
int main()
{
    console::setupConsoleEncoding();

    int res = foo(1, 2);
    cout << "\n MAIN: RES = " << res << endl;

    return 0;
}

// --- foo ---
int foo(int a, int b)
{
    int result = a + b;
    cout << "\n\t\"foo\": Я функция, меня вызвали!" << endl;
    cout << "\tRESULT = " << result << endl;
    foo2();
    return result;
}

// --- foo2 ---
void foo2()
{
    cout << "\n\t\"foo2\": Я функция, меня вызвали!" << endl;
}
