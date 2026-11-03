// C++98 — обход двумерного массива вложенными циклами.
// C++11 — списковая инициализация без =.
#include <cstdlib>
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int main()
{
    console::setupConsoleEncoding();

    const int ROWS = 5; // строки
    const int COLS = 8; // столбцы

    int arr[ROWS][COLS]{};              // инициализация нулями

    /* -- Заполнение -- */
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            arr[i][j] = rand() % 10;    // случайное число 0...9
        }
    }

    /* -- Вывод -- */
    for (int i = 0; i < ROWS; i++)      // Строки массива
    {
        for (int j = 0; j < COLS; j++)  // Столбцы строки
        {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
    return 0;
}
