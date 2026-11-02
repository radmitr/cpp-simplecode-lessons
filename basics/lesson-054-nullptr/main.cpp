// C++11 — nullptr.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/*
    Работа с динамической памятью.
    NULL и nullptr
*/

int main()
{
    console::setupConsoleEncoding();

    // -- NULL POINTER --

    int* pa = new int;      // выделение динамической памяти для int (оператор "NEW")

    *pa = 10;               // поместить в выделенную дин. память содержимое по адресу в указателе

    cout << " До delete: " << *pa << endl;

    delete pa;              // очистить выделенную динамическую память ("DELETE")

    // cout << " После delete: " << *pa << endl; // ERROR!

    pa = NULL;              // эквивалентно pa = 0;

    //cout << " После NULL: " << *pa << endl; // ERROR!

    // -- NULL --
    if (pa != NULL)
    {
        cout << pa << endl;
    }
    delete pa;              // удаление нулевого указателя разрешено

    // C++11 — nullptr: литерал типа std::nullptr_t.
    if (pa != nullptr)
    {
        cout << pa << endl;
    }
    delete pa;

    // 1) delete pa;    - сначала удалить дин.память
    // 2) pa = nullptr  - потом обнулить указатель

    return 0;
}
