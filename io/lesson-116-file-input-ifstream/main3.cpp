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

    string path = "myFile.txt";
    ifstream fin;

    fin.open(path);

    if (!fin.is_open())
    {
        cerr << "Ошибка открытия файла" << endl;
    }
    else
    {
        cout << "Файл открыт" << endl;
        string str;
        while(!fin.eof())
        {
            str = "";
            std::getline(fin, str);
            cout << str << endl;
        }
    }

    fin.close();

    return 0;
}
