#include <iostream>

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

class MyFunctor
{
public:
    int operator()(int a, int b)
    {
        cout << "Я функтор " << endl;
        return a + b;
    }

private:
    int count = 0;
};

int main(void)
{
    setupConsoleEncoding();

    MyFunctor f;

    int result = f(3, 2);

    cout << result << endl;

    return 0;
}
