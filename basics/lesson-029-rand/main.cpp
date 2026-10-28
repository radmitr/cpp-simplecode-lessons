#include <iostream>
#include <ctime>

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
