#include <iostream>
#include "sum.h"
#include "MyClass.h"

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
#endif
}

int main(void)
{
    setupConsoleEncoding();

    int result = sum(2, 3);
    cout << result << endl;

    myNamespace::MyClass mc;
    mc.printMessage("Hello, World!");

    return 0;
}
