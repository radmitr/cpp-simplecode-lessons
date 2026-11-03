// C++98 — динамические массивы и поэлементное копирование.
#include <cstddef>
#include <cstdlib>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

void fillArray(int* const arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = rand() % 10;
    }
}

void showArray(const int* const arr, const size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i] << '\t';
    }
    cout << endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    //srand(time(NULL));

    size_t size = 10;
    int* firstArray = new int[size];
    int* secondArray = new int[size];

    fillArray(firstArray, size);
    fillArray(secondArray, size);

    cout << "firstArray:\t";
    showArray(firstArray, size);
    cout << "secondArray:\t";
    showArray(secondArray, size);

    // firstArray = secondArray; // некорректно: копируется указатель, а не элементы массива

    delete[] firstArray;

    firstArray = new int[size];

    for (size_t i = 0; i < size; i++)
    {
        firstArray[i] = secondArray[i];
    }

    cout << "=========================================================================================" << endl;

    // fillArray(firstArray, size);
    // fillArray(secondArray, size);

    cout << "firstArray:\t";
    showArray(firstArray, size);
    cout << "secondArray:\t";
    showArray(secondArray, size);

    delete[] secondArray;
    delete[] firstArray;

    return 0;
}
