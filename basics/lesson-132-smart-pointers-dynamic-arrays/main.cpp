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

    const int SIZE = 5;
    int* arr = new int[SIZE] {54, 3, 74, 5, 11};

    shared_ptr<int[]> ptr(arr);

    for (int i = 0; i < SIZE; i++)
    {
        cout << i << ": " << ptr[i] << endl;
    }

    return 0;
}
