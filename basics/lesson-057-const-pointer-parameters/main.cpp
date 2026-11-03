// C++98 — const в параметрах-указателях.
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*
 *   Константные параметры при работе с динамическим массивом.
 */

 // const запрещает переназначать параметры; элементы через int* const менять можно.

 /*-----------------------------
     Заполнить дин. массив
 ------------------------------*/
void FillArray(int* const arr, const int size, const int max)
{
    srand(time(NULL));                          // установить счётчик для rand()
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % max;                  // диапазон 0..max-1
    }
}

/*-----------------------------
     Вывести дин. массив
------------------------------*/
void ShowArray(int* const arr, const int size)
{
    cout << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "  " << arr[i] << "\t";
    }
    cout << endl << endl;
}

int main()
{
    console::setupConsoleEncoding();

    int size = 5, max = 100;
    int* arr = new int[size];

    FillArray(arr, size, max);
    ShowArray(arr, size);

    delete[] arr; // Для каждого new[] требуется delete[].

    return 0;
}
