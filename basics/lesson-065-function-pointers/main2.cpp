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

int foo1(int a)
{
    return a - 1;
}

int foo2(int a)
{
    return a * 2;
}

int main(void)
{
    setupConsoleEncoding();

    int(*fooPointer)(int);

    fooPointer = foo2;
    cout << fooPointer(5) << endl;

    return 0;
}
