// C++98 — передача аргументов по значению.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/* функции передача параметров (аргументов) */

double sum(double a, double b, double c)
{
    return a + b + c;
}

int main()
{
    console::setupConsoleEncoding();

    cout << "\tSUM = " << sum(2.55, 7.67, 23.81) << endl;

    return 0;
}
