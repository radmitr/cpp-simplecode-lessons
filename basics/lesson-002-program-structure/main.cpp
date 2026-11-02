// C++98 — структура программы, main() и return.
#include "../../common/console.hpp"
#include <iostream>
#include <string>
#include <clocale>

using namespace std;

int main()
{
    console::setupConsoleEncoding();
    //setlocale(0, "");
    //setlocale(LC_ALL, "ru");
    //setlocale(LC_ALL, "Rus");

    cout << "\n Привет МИР!" << endl;

    return 0;
}
