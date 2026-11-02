// C++98 — локальные и глобальные переменные, области видимости.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/*
    Область видимости
    Глобальные переменные и локальные переменные
*/

int value = 0;      // глобальная переменная (область видимости начинается с объявления) - инициализируется по умолчанию нулём

void foo()
{
    int z = 0;      // локальная переменная функции
    value = 1;      // глобальная переменная
}

int main()
{
    console::setupConsoleEncoding();

    int b;          // Локальная переменная main(); до присваивания читать нельзя.

    if (true)
    {
        int a = 0;  // локальная переменная в области видимости блока if
        b = 1;      // local var (from main)
        cout << "(if) local a = " << a << endl;
        cout << "(if) local b = " << b << endl;
    }

    int a = 123;
    b = 2;
    cout << "(main) local a = " << a << endl;
    cout << "(main) local b = " << b << endl;

    // ограничение области видимости
    {
        int v = 123;
    }

    // v = 234; // переменная не видна
    value = 2;  // глобальная переменная

    return 0;
}
