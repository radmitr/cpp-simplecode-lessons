#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>

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

    wfstream fs("myFile.txt", ios::in | ios::out | ios::app);

    // Устанавливаем UTF-8 для файла
    fs.imbue(locale(fs.getloc(),
        new codecvt_utf8<wchar_t, 0x10ffff, consume_header>()));

    int value;
    wstring msg;

    wcout << L"Выберите действие:\n";
    wcout << L"1 - Записать сообщение\n";
    wcout << L"2 - Прочитать все сообщения\n";
    wcin >> value;

    wcin.ignore();

    if (value == 1)
    {
        wcout << L"Введите ваше сообщение!" << endl;
        getline(wcin, msg);
        fs << msg << L"\n";
    }
    else if (value == 2)
    {
        wcout << L"Сообщения из файла:" << endl;
        fs.seekg(0);

        while (getline(fs, msg))
        {
            wcout << msg << endl;
        }
    }

    fs.close();

    return 0;
}
