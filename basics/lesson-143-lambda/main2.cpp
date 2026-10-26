#include <iostream>
#include <functional>
#include <vector>

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

    doWork(vc, [](int a) {
        cout << "Lambda with parameter: " << a << endl;
    });

    return 0;
}
