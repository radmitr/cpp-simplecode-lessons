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
    void operator()()
    {
        cout << "Я функтор " << count << endl;
        count++;
    }

private:
    int count = 0;
};

int main(void)
{
    setupConsoleEncoding();

    MyFunctor f;

    for (size_t i = 0; i < 5; i++)
    {
        f();
    }

    return 0;
}
