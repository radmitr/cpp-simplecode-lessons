// C++98 — основные типы языка (обзор в комментариях).
#include <clocale>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

int main()
{
    console::setupConsoleEncoding();
    /*
     * Числовые типы: short, int, long, float, double.
     * Символьный тип: char; логический тип: bool.
     * Размеры зависят от реализации. sizeof(char) всегда равен 1 байту C++.
     * long используется и сегодня; в Windows и Linux его размеры могут различаться.
     */

    cout << " \n Привет!\n";

    return 0;
}
