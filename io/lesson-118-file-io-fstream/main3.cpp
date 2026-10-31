#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <codecvt>
#include <clocale>

#ifdef _WIN32
#include <cstdio>
#include <fcntl.h>
#include <io.h>
#endif

void setupWideStandardIO()
{
#ifdef _WIN32
    _setmode(_fileno(stdin), _O_U8TEXT);
    _setmode(_fileno(stdout), _O_U8TEXT);
#else
    std::setlocale(LC_ALL, "");
#endif
}

int main(void)
{
    setupWideStandardIO();

    std::wfstream fs("myFile.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!fs)
    {
        std::cerr << "Cannot open myFile.txt\n";
        return 1;
    }

    // Устанавливаем UTF-8 для файла
    auto* translator = new std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>();
    std::locale settings(fs.getloc(), translator);  // прежние настройки + переводчик
    fs.imbue(settings);                             // назначить их файлу fs

    int value;
    std::wstring msg;

    std::wcout << L"Выберите действие:\n";
    std::wcout << L"1 - Записать сообщение\n";
    std::wcout << L"2 - Прочитать все сообщения\n";
    if (!(std::wcin >> value))
    {
        std::cerr << "Invalid menu choice\n";
        return 1;
    }

    std::wcin.ignore(); // Пропускаем Enter после выбора пункта меню

    if (value == 1)
    {
        std::wcout << L"Введите ваше сообщение!" << std::endl;
        std::getline(std::wcin, msg);
        fs << msg << L"\n";
    }
    else if (value == 2)
    {
        std::wcout << L"Сообщения из файла:" << std::endl;
        fs.seekg(0);

        while (std::getline(fs, msg))
        {
            std::wcout << msg << std::endl;
        }
    }

    fs.close();

    return 0;
}
