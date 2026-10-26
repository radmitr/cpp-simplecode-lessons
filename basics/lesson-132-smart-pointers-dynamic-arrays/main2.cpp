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

    cout << "Введите размер массива: ";
    int size = 5;
    cin >> size;

    int* arr = new int[size] {};

    shared_ptr<int[]> ptr(arr);

    for (int i = 0; i < size; i++)
    {
        ptr[i] = rand() % 100;
        cout << i << ": " << ptr[i] << endl;
    }

    return 0;
}
