// C++98 — выделение и освобождение памяти через new и delete.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/*
    Работа с динамической памятью.
    Операторы выделения памяти new и delete.
*/

int main()
{
    console::setupConsoleEncoding();

    // -- NEW and DELETE --

    int* pa = new int;      // выделение динамической памяти для int (оператор "NEW")

    *pa = 10;               // поместить в выделенную дин. память содержимое (данные) по адресу в указателе

    cout << "\n NEW: " << pa << ": " << *pa << endl;

    delete pa;              // очистить выделенную динамическую память ("DELETE")

    return 0;
}
