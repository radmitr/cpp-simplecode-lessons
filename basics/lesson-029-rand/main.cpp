#include <iostream>
#include <ctime>

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

    srand(time(NULL));

    const int SIZE = 10;

    int arr[SIZE];

    for (size_t i = 0; i < SIZE; i++)
    {
        arr[i] = rand() % 100;
    }

    for (size_t i = 0; i < SIZE; i++)
    {
        cout << arr[i] << endl;
    }

    return 0;
}
