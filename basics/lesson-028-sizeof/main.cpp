// C++98 — sizeof типов и переменной.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

int main()
{
    console::setupConsoleEncoding();

    int a;

    cout << "INT: " << sizeof(int) << " bytes" << endl;
    cout << "DOUBLE: " << sizeof(double) << " bytes" << endl;
    cout << sizeof(a) << endl;

    return 0;
}
