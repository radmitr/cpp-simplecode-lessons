// C++11 — std::function.
#include <functional>
#include <iostream>
#include <vector>

#include "../../common/console.hpp"

using namespace std;

void foo(int a)
{
    if (a > 10 && a < 40)
    {
        cout << "foo " << a << endl;
    }
}

void bar(int a)
{
    if (a % 2 == 0)
    {
        cout << "bar " << a << endl;
    }
}

void baz(int a)
{
    cout << "baz " << endl;
}

void doWork(vector<int> vc, function<void(int)> f)
{
    for (auto el : vc)
    {
        f(el);
    }
}

void doWork2(vector<int> vc, vector<function<void(int)>> funcVector)
{
    for (auto el : vc)
    {
        for (auto &fel : funcVector)
        {
            fel(el);
        }
    }
}

int main(void)
{
    console::setupConsoleEncoding();

    vector<int> vc = {1, 51, 4, 10, 44, 98, 8, 12, 22, 29, 49};

    doWork(vc, foo);
    cout << '\n';
    doWork(vc, bar);
    cout << "\n\n";

    vector<function<void(int)>> fVector;

    fVector.emplace_back(foo);
    fVector.emplace_back(bar);
    fVector.emplace_back(baz);

    doWork2(vc, fVector);

    return 0;
}
