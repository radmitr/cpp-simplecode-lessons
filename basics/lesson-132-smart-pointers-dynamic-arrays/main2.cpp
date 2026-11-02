// C++11 — std::shared_ptr; C++17 — std::shared_ptr<T[]>.
#include <cstdlib>
#include <iostream>
#include <memory>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

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
