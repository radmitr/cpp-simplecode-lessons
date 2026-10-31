#include <iostream>
#include <string>
#include <fstream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

int main(void)
{
    setupConsoleEncoding();

    fstream fs("myFile.txt", ios::in | ios::out | ios::app);
    if (!fs)
    {
        std::cerr << "Cannot open myFile.txt\n";
        return 1;
    }

    int value;
    string msg;

    cout << "Выберите действие:\n";
    cout << "1 - Записать сообщение\n";
    cout << "2 - Прочитать все сообщения\n";
    if (!(cin >> value))
    {
        cerr << "Invalid menu choice\n";
        return 1;
    }

    if (value == 1)
    {
        cout << "Введите ваше сообщение!" << endl;
        cin >> msg;
        fs << msg << "\n";
    }
    else if (value == 2)
    {
        cout << "Сообщения из файла:" << endl;
        fs.seekg(0);

        while (fs >> msg)
        {
            cout << msg << endl;
        }
    }

    fs.close();

    return 0;
}
