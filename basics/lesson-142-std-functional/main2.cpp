#include <iostream>
#include <functional>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

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
    setupConsoleEncoding();

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
