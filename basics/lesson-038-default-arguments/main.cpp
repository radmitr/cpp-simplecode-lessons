// C++98 — аргументы функций по умолчанию.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/* Аргументы (параметры) по умолчанию */

// --- foo ---
void foo(int q, int a = 5, double b = 0.5) // q и b не используются; a задаёт число звёздочек.
{
    cout << endl;
    for (int i = 0; i < a; i++)
    {
        cout << "*";
    }
    cout << endl;
}

// *** main ***
int main()
{
    console::setupConsoleEncoding();

    foo(2);             // a и b берутся по умолчанию
    foo(4, 24);         // q и a заданы явно
    foo(4, 10, 1.5);    // все три аргумента заданы явно
    foo(4);             // задан только обязательный q

    return 0;
}
