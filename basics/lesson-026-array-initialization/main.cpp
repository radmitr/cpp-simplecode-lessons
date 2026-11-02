// C++98 — инициализация массивов списком после =.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/* инициализация массива */

int main()
{
    console::setupConsoleEncoding();

    //int arr[]{ 1, 66, 12, 2 };            // C++11 — инициализация без =
    //int arr[4]{ 1, 66, 12, 2 };           // c данными
    //int arr[4]{};                         // c нулями

    int arr[4] = { 1, 66, 12, 2 };          // C++98 — список после =

    cout << arr[3] << endl;

    return 0;
}
