// C++98 — объявления и определения в нескольких файлах.
#include <iostream>

#include "../../../common/console.hpp"
#include "MyClass.h"
#include "sum.h"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    int result = sum(2, 3);
    cout << result << endl;

    myNamespace::MyClass mc;
    mc.printMessage("Hello, World!");

    return 0;
}
