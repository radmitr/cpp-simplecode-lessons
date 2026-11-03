// C++98 — ввод через std::cin и проверка состояния потока.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

int main()
{
    console::setupConsoleEncoding();

    int Var, Var2;

    cout << " Введите первое число: ";
    if (!(cin >> Var))
    {
        cerr << "Invalid input\n";
        return 1;
    }                                       // cin - <iostream>

    cout << " Введите второе число: ";
    if (!(cin >> Var2))
    {
        cerr << "Invalid input\n";
        return 1;
    }

    cout << " Число 1: " << Var << endl << " Число 2: " << Var2 << endl;

    return 0;
}
