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

int main(void)
{
    setupConsoleEncoding();

    int a = 55;
    int b = 10;

    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    function f = [a]() {
        cout << a << " " << &a << endl;
    };

    function f2 = [&a, b]() mutable {
        cout << a << " " << &a << endl;
        a = 1323;
        cout << b << " " << &b << endl;
        b = 11;
    };

    function f3 = [=]() mutable {
        cout << a << " " << &a << endl;
        a = 1324;
        cout << b << " " << &b << endl;
        b = 12;
    };

    function f4 = [&]() {
        cout << a << " " << &a << endl;
        a = 1325;
        cout << b << " " << &b << endl;
        b = 13;
    };

    f();
    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    f2();
    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    f3();
    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    f4();
    cout << "a=" << a << " " << &a << endl;
    cout << "b=" << b << " " << &b << '\n' << endl;

    return 0;
}
