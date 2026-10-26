#include <iostream>
#include <functional>

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

void foo()
{
    cout << "foo()" << endl;
}

void bar()
{
    cout << "bar()" << endl;
}

int sum(int a, int b)
{
    return a + b;
}

int main(void)
{
    setupConsoleEncoding();

    function<void()> f;
    f = foo;
    f();

    f = bar;
    f();

    function<int(int, int)> f2;
    f2 = sum;
    int result = f2(2, 3);
    cout << "result=" << result << endl;

    return 0;
}
