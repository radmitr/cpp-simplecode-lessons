// C++98 — функциональные макросы.
#include <iostream>

#include "../../common/console.hpp"

// МАКРОС
#define FOO(x,y) ((x)*(y))

using namespace std;

/*
    Препроцессор
    #define
    макрос функция
*/

int main()
{
    console::setupConsoleEncoding();

    cout << FOO(5, 6) << endl;

    return 0;
}
