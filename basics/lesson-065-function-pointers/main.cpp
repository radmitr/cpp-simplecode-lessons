#include <iostream>

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

void foo1()
{
    cout << "void foo1()" << endl;
}

void foo2()
{
    cout << "void foo2()" << endl;
}

int main(void)
{
    setupConsoleEncoding();

    void(*fooPointer)();

    fooPointer = foo2;
    fooPointer();

    return 0;
}
