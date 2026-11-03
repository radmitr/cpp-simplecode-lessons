// C++98 — динамический массив указателей на строки.
#include <cstdlib>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/*
 *     Двумерный динамический массив
 *     это одномерный массив одномерных массивов
 */

int main()
{
    console::setupConsoleEncoding();

    // --- DYN ARRAY 2D ---

    int rows;                           // Число строк.
    int cols;                           // Число столбцов в каждой строке.

    // --- ВВОД РАЗМЕРНОСТИ ---

    cout << " \nEnter ROWS count: ";
    if (!(cin >> rows) || rows < 1 || rows > 100)
    {
        cerr << "Invalid input\n";
        return 1;
    }

    cout << " \nEnter COLS count: ";
    if (!(cin >> cols) || cols < 1 || cols > 100)
    {
        cerr << "Invalid input\n";
        return 1;
    }

    // --- (1) СОЗДАНИЕ ДВУМЕРНОГО МАССИВА ---

    int** arr = new int* [rows]; // Массив указателей на строки.
    for (int i = 0; i < rows; ++i)
        arr[i] = 0; // Эта строка ещё не выделена.
    // delete [] arr;                   // освободить память от массива

    try
    {
        for (int i = 0; i < rows; i++)
        {
            arr[i] = new int[cols];         // динамическая память для одномерных массивов (колонки)
        }
    }
    catch (...)
    {
        // Нулевые указатели обозначают ещё не созданные строки.
        for (int i = 0; i < rows; ++i)
            delete[] arr[i];
        delete[] arr;
        cerr << "Could not allocate matrix\n";
        return 1;
    }

    /////////////////////////////////////////////////

    // --- (2) ЗАПОЛНЕНИЕ МАССИВА ---

    //srand(time(NULL));                        // установить счётчик для rand()
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            arr[i][j] = rand() % 20;            // random 0..19
        }
    }

    // --- (3) ВЫВОД ---

    cout << endl;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cout << arr[i][j] << "\t";          // вывод на console
        }
        cout << endl;                           // построчно
    }

    /////////////////////////////////////////////////

    // --- УДАЛЕНИЕ ДВУМЕРНОГО МАССИВА ---

    for (int i = 0; i < rows; i++)
    {
        delete[] arr[i];                        // удалить одномерные подмассивы
    }
    delete[] arr;                               // удалить массив "строк"

    return 0;
}
