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

void doWork(vector<int> vc, function<void(int)> f)
{
    for (auto el : vc)
    {
        f(el);
    }
}

int main(void)
{
    setupConsoleEncoding();

    vector<int> vc = {1, 51, 4, 10, 44, 98, 8, 12, 22, 29, 49};

    function<void(int)> f;

    f = [](int a)
    {
        cout << "Lambda with parameter: " << a << endl;
    };

    doWork(vc, f);

    return 0;
}
