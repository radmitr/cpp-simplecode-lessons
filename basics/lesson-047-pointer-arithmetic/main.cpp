// C++98 — арифметика указателей внутри массива.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*--- АРИФМЕТИКА УКАЗАТЕЛЕЙ ---*/

int main()
{
    console::setupConsoleEncoding();

    // В выражениях имя массива часто преобразуется в указатель на первый элемент.

    const int SIZE = 5;

    int arr[SIZE] = { 4, 55, 79, 1, 4 };

    cout << endl;

    cout << "Массив \"arr\":" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "\tarr[" << i << "]\t" << arr[i] << endl;
    }

    cout << endl;

    /*===================================================================*/

    // pArr хранит адрес первого элемента массива arr.
    // Новый указатель на массив с тем же адресом (адрес первого элемента массива)
    int* pArr = arr;
    cout << "Массив \"*pArr\":" << endl;
    for (int i = 0; i < SIZE; i++) // перебор элементов в массива по адресу указателя.
    {
        cout << "\tpArr[" << i << "] = \t" << pArr[i] << endl;
    }

    cout << endl;

    cout << "\tADDRESS arr:\t" << arr << endl;
    cout << "\tADDRESS pArr:\t" << pArr << endl;

    cout << endl;

    cout << "==================================\n";

    // СОДЕРЖИМОЕ МАССИВА
    cout << "Массив \"*pArr:\"" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        cout << "\tpArr: " << (pArr + i) << "\t" << *(pArr + i) << endl;    // арифметика указателей *(pArr+i) - переход к след. адресу массива
    }

    cout << "==================================\n";

    // АДРЕСА И СОДЕРЖИМОЕ МАССИВА
    for (int i = 0; i < SIZE; i++)
    {
        cout << "\tarr: " << arr + i << ":\t" << *(arr + i) << endl;
    }

    return 0;
}
