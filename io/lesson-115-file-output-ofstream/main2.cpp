#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstring>

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

    const string path = "myFile.txt";
    ofstream fout;

    fout.open(path, ios::out);

    if (!fout.is_open())
    {
        cerr << "Ошибка открытия файла: " << path << endl;
        cerr << "Код ошибки: " << strerror(errno) << endl;
        return EXIT_FAILURE;
    }

    try
    {
        fout << "Это наши данные" << endl;

        if (fout.fail())
        {
            cerr << "Ошибка записи в файл" << endl;
            fout.close();
            return EXIT_FAILURE;
        }

        cout << "Данные успешно записаны в файл: " << path << endl;
    }
    catch (const exception& e)
    {
        cerr << "Исключение при работе с файлом: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    // Файл закроется автоматически при выходе из области видимости
    // но можно и явно закрыть
    fout.close();

    return 0;
}
