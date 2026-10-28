#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <system_error>

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

bool writeToFile(const string& filename, const vector<string>& data)
{
    ofstream file(filename);
    if (!file)
    {
        cerr << "Ошибка открытия файла: " << filename << endl;
        return false;
    }

    for (const auto& line : data)
    {
        file << line << '\n';
    }

    if (!file)
    {
        cerr << "Ошибка записи в файл: " << filename << endl;
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    setupConsoleEncoding();

    string filename = "myFile.txt";

    // Если передан аргумент командной строки - используем его как имя файла
    if (argc > 1)
    {
        filename = argv[1];
    }

    vector<string> data = {
        "Это наши данные",
        "Вторая строка данных",
        "Третья строка"
    };

    if (writeToFile(filename, data))
    {
        cout << "Файл '" << filename << "' успешно создан!" << endl;
        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}
