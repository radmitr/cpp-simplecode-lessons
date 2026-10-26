#include <iostream>
#include <memory>

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

    const int SIZE = 5;
    int* arr = new int[SIZE] {54, 3, 74, 5, 11};

    shared_ptr<int[]> ptr(arr);

    for (int i = 0; i < SIZE; i++)
    {
        cout << i << ": " << ptr[i] << endl;
    }

    return 0;
}
