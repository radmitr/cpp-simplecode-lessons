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

    string path = "myFile.txt";
    ofstream fout;

    fout.open(path, ofstream::app);

    if (!fout.is_open())
    {
        cerr << "Ошибка открытия файла" << endl;
    }
    else
    {
        //fout << "Это наши данные";
        fout << "\nНовые данные";
    }

    fout.close();

    return 0;
}
