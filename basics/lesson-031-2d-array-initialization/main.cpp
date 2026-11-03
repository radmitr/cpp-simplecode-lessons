// C++98 — двумерные массивы и вложенные списки инициализации.
// C++11 — списковая инициализация без =.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/* 2D Array Initialization */

int main()
{
    console::setupConsoleEncoding();

    const int ROW = 3;      // строки
    const int COL = 4;      // колонки

    int arr_1D[]{ 11,23,34,56 };                    // одномерный массив - ручная инициализация

    int arr_2D[][COL] =                             // ручная инициализация 2D Array ("= "- не обязательно!)
    {
        {11, 22, 33, 44},
        {55, 66, 77, 88},
        {101, 344, 23}                              // 4-й элемент будет инициализирован нулём
    };

    int arr[ROW][COL]{};                            // объявить 2D Array с нулями

    cout << "arr[0][0] = " << arr[0][0] << endl;
    cout << "arr[1][1] = " << arr[1][1] << endl;

    arr[0][0] = 111;
    arr[1][1] = 999;

    cout << "------------------------" << endl;
    cout << "arr[0][0] = " << arr[0][0] << endl;
    cout << "arr[1][1] = " << arr[1][1] << endl;

    return 0;
}
