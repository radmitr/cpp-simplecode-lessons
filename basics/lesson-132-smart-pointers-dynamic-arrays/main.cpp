// C++11 — списковая инициализация массива; C++17 — std::shared_ptr<T[]>.
#include <iostream>
#include <memory>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    const int SIZE = 5;
    int* arr = new int[SIZE] {54, 3, 74, 5, 11};

    shared_ptr<int[]> ptr(arr);

    for (int i = 0; i < SIZE; i++)
    {
        cout << i << ": " << ptr[i] << endl;
    }

    return 0;
}
