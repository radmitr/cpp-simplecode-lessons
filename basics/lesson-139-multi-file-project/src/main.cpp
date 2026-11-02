// C++98 — объявления и определения в нескольких файлах.
#include <iostream>
#include "sum.h"
#include "MyClass.h"

#include "../../../common/console.hpp"

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
