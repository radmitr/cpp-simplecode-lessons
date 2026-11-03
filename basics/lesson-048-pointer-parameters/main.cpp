// C++98 — передача указателя в функцию.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*
    Передача параметров по указателю
    Как вернуть два и более значений функции
*/

// Без указателя по значению
void Foo(int aa) // aa из main() передаётся по значению в локальный параметр aa.
{
    aa++;
}

// С указателем (адресом)
void Foo2(int* pa, int* pb)
{
    // разыменование памяти (содержимое ячейки памяти)
    // сначала разыменовать, потом инкрементировать
    (*pa)++;
    (*pb) = 555;
}

int main()
{
    console::setupConsoleEncoding();

    // без указателя - по значению
    int aa = 0;
    cout << aa << endl;
    Foo(aa);
    cout << aa << endl;

    cout << "\n==================================\n";

    int a = 0, b = 0;
    cout << a << endl;
    Foo2(&a, &b);           // адрес ячейки памяти со значением переменной
    cout << a << endl;
    cout << b << endl;

    return 0;
}
