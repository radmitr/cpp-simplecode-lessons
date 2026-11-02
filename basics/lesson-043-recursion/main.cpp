// C++98 — рекурсивные вызовы функций.
#include "../../common/console.hpp"
#include <iostream>
using namespace std;

int Foo(int a)
{
    if (a < 1) return 0;    // если конец рекурсии - выйти с нулём
    a--;                    // уменьшить счётчик рекурсии

    cout << "\tfoo (recursion test): a = " << a << endl;

    return Foo(a);
}

int main()
{
    console::setupConsoleEncoding();
    Foo(5);
    return 0;
}
