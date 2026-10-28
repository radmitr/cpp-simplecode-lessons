#include <iostream>
#include <memory>

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
