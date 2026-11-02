// C++98 — ветвление if / else.
#include "../../common/console.hpp"
#include <iostream>

using namespace std;

/*
    Конструкция условного выбора if
    Лесенка if-else-if
*/

int main()
{
    console::setupConsoleEncoding();

    // EXAMPLE 1
    bool isRain = false;

    if (isRain)
    {
        cout << "Идёт дождь, нам нужен зонт!" << endl;
    }
    else
    {
        cout << "Дождя нет, зонт не нужен!" << endl;
    }

    // EXAMPLE 2
    int a;

    cout << "Введите число: ";
    if (!(cin >> a))
    {
        cerr << "Invalid input\n";
        return 1;
    }

    if (a < 5)
    {
        cout << "Ваше число < 5!" << endl;
    }
    else if (a == 5)
    {
        cout << "Ваше число == 5!" << endl;
    }
    else
    {
        cout << "Ваше число > 5!" << endl;
    }

    return 0;
}
