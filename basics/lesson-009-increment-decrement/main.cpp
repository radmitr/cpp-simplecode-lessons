// C++98 — префиксные и постфиксные ++ и --.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

// инкремент и декремент

int main()
{
    console::setupConsoleEncoding();

    int a = 1, b = 1;

    // ПОСТФИКСНАЯ ФОРМА: a++, a--
    cout << "\t до " << a << endl;
    cout << " postfix++: " << endl;
    cout << "\t после " << a++ << endl;
    cout << "\t финал " << a << endl << endl;

    // ПРЕФИКСНАЯ ФОРМА: ++b, --b
    cout << "\t до " << b << endl;
    cout << " ++prefix: " << endl;
    cout << "\t после " << ++b << endl;
    cout << "\t финал " << b << endl << endl;

    a = 1;
    b = 0;
    ++a; // Изменение завершается до чтений a в следующем выражении.
    b = a * a;
    cout << endl;
    cout << "\t" << b << endl;

    return 0;
}
