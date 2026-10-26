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

    auto f = []()->int {
        return 1.45;
    };

    f();

    function<float()> f2 = []() {
        return 1.45;
    };

    f2();

    function<float()> f3 = []()->int {
        return 1.45;
    };

    f3();

    return 0;
}
