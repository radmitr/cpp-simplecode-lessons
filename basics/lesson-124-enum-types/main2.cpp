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

enum Speed
{
    MIN = 150,
    RECOMMEND = 600,
    MAX = 800
};

int main(void)
{
    setupConsoleEncoding();

    cout << Speed::MIN << endl;
    cout << Speed::RECOMMEND << endl;
    cout << Speed::MAX << endl;

    Speed speed = Speed::MAX;
    cout << speed << endl;

    return 0;
}
