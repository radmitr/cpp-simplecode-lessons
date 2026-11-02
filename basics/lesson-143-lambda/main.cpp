// C++11 — лямбда-выражения.
#include <iostream>
#include <functional>
#include <vector>

#include "../../common/console.hpp"

using namespace std;

void doWork(vector<int> vc, function<void(int)> f)
{
    for (auto el : vc)
    {
        f(el);
    }
}

int main(void)
{
    console::setupConsoleEncoding();

    vector<int> vc = {1, 51, 4, 10, 44, 98, 8, 12, 22, 29, 49};

    function<void(int)> f;

    f = [](int a)
    {
        cout << "Lambda with parameter: " << a << endl;
    };

    doWork(vc, f);

    return 0;
}
