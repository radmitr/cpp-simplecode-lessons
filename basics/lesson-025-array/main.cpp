// C++98 — массивы; C++11 — инициализация пустым списком.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

/* массивы */

int main()
{
    console::setupConsoleEncoding();

    // Тип_данных имя [кол-во элементов];
    int arr[4]{};
    arr[0] = 5;
    cout << arr[0] << endl;

    return 0;
}
