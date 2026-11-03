// C++98 — возврат нескольких результатов через указатели.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*
    Передача аргументов по указателю.
    Как вернуть два и более значения из функции
*/

// Функция с любым числом параметров с учётом указателей
// Указатели на принимаемые переменные ('*')
void foo(int* pa, int* pb, int* pc)
{

    (*pa) = 555;

    (*pb)++;

    (*pc) = -20;
}

/**************************************************************/

void foo2(int& a, int& b, int& c)
{
    a = 10;
    b *= 2;
    c -= 100;
}

int main()
{
    console::setupConsoleEncoding();

    // -- POINTERS (УКАЗАТЕЛИ) --

    int a = 0, b = 0, c = 1;

    cout << endl;
    cout << " a = " << a << endl;
    cout << " b = " << b << endl;
    cout << " c = " << c << endl;

    cout << "\n---------- foo() ----------" << endl;
    foo(&a, &b, &c);                        // Передаем адреса переменных ('&')

    cout << endl;
    cout << " a = " << a << endl;
    cout << " b = " << b << endl;
    cout << " c = " << c << endl;

    /********************************************************************************/

    // -- RETURN VALUES FUNCTION FROM REFERENCES --

    int a2 = 0, b2 = 4, c2 = 34;
    cout << "\n***************************************\n" << endl;
    cout << " a2 = " << a2 << endl;
    cout << " b2 = " << b2 << endl;
    cout << " c2 = " << c2 << endl;

    cout << endl;
    cout << "foo2: " << endl;
    foo2(a2, b2, c2);

    cout << " a2 = " << a2 << endl;
    cout << " b2 = " << b2 << endl;
    cout << " c2 = " << c2 << endl;

    return 0;
}
