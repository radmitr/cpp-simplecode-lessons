#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
#endif
}

int main(void)
{
    setupConsoleEncoding();

    fstream fs("myFile.txt", ios::in | ios::out | ios::app | ios::binary);

    int value;
    string msg;

    cout << "Выберите действие:\n";
    cout << "1 - Записать сообщение\n";
    cout << "2 - Прочитать все сообщения\n";
    cin >> value;

    cin.ignore();

    if (value == 1)
    {
        cout << "Введите ваше сообщение!" << endl;
        getline(cin, msg);
        fs << msg << "\n";
    }
    else if (value == 2)
    {
        cout << "Сообщения из файла:" << endl;
        fs.seekg(0);

        while (getline(fs, msg))
        {
            cout << msg << endl;
        }
    }

    fs.close();

    return 0;
}
