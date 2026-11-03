// C++98 — динамические массивы, new[] и delete[].
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*
    динамический массив
*/

int main()
{
    console::setupConsoleEncoding();

    // -- DYN ARRAY 1D --

    int size = 0;
    cout << "\n  Enter array size: ";
    if (!(cin >> size) || size < 1 || size > 100)
    {
        cerr << "Invalid input\n";
        return 1;
    }

    int* arr = new int[size];
    // delete [] arr; // удалить массив

    // Заполнить массив
    srand((unsigned)time(NULL));                // установить генератор случайных чисел
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;                  // получить случайное число 0..99
    }

    cout << endl;

    // Просмотреть массив
    for (int i = 0; i < size; i++)
    {
        cout << arr + i << ": ";                // адреса на элементы
        cout << arr[i];                         // содержимое элементов (данные)
        cout << " - " << *(arr + i) << endl;
    }

    delete[] arr; // Для каждого new[] требуется delete[].

    return 0;
}
