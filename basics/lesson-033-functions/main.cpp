// C++98 — объявление, определение и вызов функции.
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*----------------------------------------
    возвращаемое_значение имя (параметры)
    {
        код функции...
    }
-----------------------------------------*/

int foo(int);
void foo2(int);
int sum(int, int);

/*************************
           MAIN
**************************/

int main()
{
    console::setupConsoleEncoding();

    srand(time(NULL));
    cout << "RAND = " << rand() << endl;

    for (int i = 0; i < 5; i++)
    {
        foo(i);
        foo2(i);
    }

    int a = 1, b = 2;
    int c = sum(a, b);
    cout << " C = " << c << endl;

    return 0;
}

/*************************
         FUNCTIONS
**************************/

// --- foo ---
int foo(int i)
{
    cout << "foo(): Я функция. Меня вызвали! - " << i << endl;
    return 0;
}

// --- foo2 ---
void foo2(int n)
{
    cout << "\tfoo2(): Test function! - " << n << endl;
}

// --- sum ---
int sum(int a, int b)
{
    int result = a + b;
    cout << "///////////////////////////////////" << endl;
    cout << "\tSUM: RESULT = " << result << endl;
    cout << "///////////////////////////////////" << endl;
    return result;
}
