// C++11 — std::function.
#include <iostream>
#include <functional>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

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
