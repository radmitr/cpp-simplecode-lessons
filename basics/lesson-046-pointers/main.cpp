// C++98 — указатели, взятие адреса и разыменование.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

// -- Pointers and Links --

int main()
{
    console::setupConsoleEncoding();

    // -- POINTERS (УКАЗАТЕЛИ) --

    int a = 5;
    double b = 1.495;
    cout << " a = " << a << endl;

    int* pa = &a;       // Адрес (присвоить  указателю адрес ячейки с содержимым)
    double* pb = &b;    // Адрес для типа double
    cout << "\n ---> Адрес для \"int a\" --> " << pa << endl;
    cout << "\n ---> Адрес для \"double b\" --> " << pb << endl;

    int* px = &a;
    int* px2 = &a;
    cout << " a = " << a << endl;

    cout << "\n ---> Адрес для \"int *px\"\t" << px << endl;
    cout << "\n ---> Адрес для \"int *px2\"\t" << px2 << endl;

    *px = 2;
    cout << " a = " << a << endl;

    return 0;
}
