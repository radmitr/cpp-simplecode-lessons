// C++98 — передача аргументов по ссылке.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*
    Ссылочные параметры. Передача аргументов по ссылке.
*/

// параметр по значению
void  foo(int a)
{
    a = 1;
}

// параметр по ссылке
void  foo2(int& a)
{
    a = 2;
}

// параметр по указателю
void  foo3(int* a)
{
    *a = 3;
}

int main()
{
    console::setupConsoleEncoding();

    // -- REF-PAR-FUNCTIONS --

    int value = 5;
    cout << endl;
    cout << "START: value = " << value << endl << endl;;

    foo(value);
    cout << " foo (a): value = " << value << endl << endl;

    foo2(value);
    cout << " foo2 (&a): value = " << value << endl << endl;

    foo3(&value);
    cout << " foo3 (*a): value = " << value << endl << endl;

    cout << "END: value = " << value << endl;

    return 0;
}
