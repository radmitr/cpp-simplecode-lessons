// C++98 — ссылки на переменные.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/*
 *  ссылки
 */

int main()
{
    console::setupConsoleEncoding();

    // -- REFERENCES (ССЫЛКИ) --

    int a = 5;          // 1. Значение переменной a.

    int* pa = &a;       // 2. Указатель pa хранит адрес a; *pa обращается к значению.

    int& aref = a;      // 3. Ссылка aref — другое имя a; &aref даёт адрес a.

    cout << " Адрес pa:\t" << pa << endl;               // адрес
    cout << " Адрес &aref:\t" << &aref << endl;         // адрес
    cout << endl;
    cout << "Содержимое *pa = \t" << *pa << endl;       // содержимое
    cout << "Содержимое aref = \t" << aref << endl;     // содержимое

    /* ссылки обеспечивают прямой доступ к данным */
    aref = aref + 2;        // 5 + 2 = 7
    aref = aref - 2;        // 7 - 2 = 5

    return 0;
}
