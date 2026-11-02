// C++98 — switch, case, default и break.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

// Оператор множественного выбора

int main()
{
    console::setupConsoleEncoding();

    int a;
    cout << "Введите число: ";
    if (!(cin >> a))
    {
        cerr << "Invalid input\n";
        return 1;
    }

    switch (a)
    {
    case 1:
        cout << "Вы ввели 1" << endl;
        break;

    case 2:
        cout << "Вы ввели 2" << endl;
        break;

    default:
        cout << "Я не знаю этого числа!" << endl;
        break;
    }

    return 0;
}
