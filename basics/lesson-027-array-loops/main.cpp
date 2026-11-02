// C++98 — заполнение массива через rand() % 100.
// C++11 — списковая инициализация без =.
#include "../../common/console.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

/* вывод статического массива  */

int main()
{
    console::setupConsoleEncoding();

    const int size = 5;

    int arr[size]{ 55, 511, 2, 123, 95 };

    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100;  // 0..99
    }

    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << endl;
    }

    return 0;
}
