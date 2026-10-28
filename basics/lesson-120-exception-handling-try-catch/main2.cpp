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

    // string path = "myFile.txt";
    string path = "myFile.tx";

    ifstream fin;
    fin.exceptions(ifstream::badbit | ifstream::failbit);

    try
    {
        cout << "Попытка открыть файл!" << endl;
        fin.open(path);
        cout << "Файл успешно открыт!" << endl;

        fin.close();
    }
    catch(const ifstream::failure& e)
    {
        cerr << "Ошибка открытия файла!" << endl;
        cerr << e.what() << endl;
        cerr << e.code() << endl;
    }

    return 0;
}
