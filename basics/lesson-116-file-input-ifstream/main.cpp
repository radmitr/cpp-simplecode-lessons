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
    ifstream fin;

    fin.open(path);

    if (!fin.is_open())
    {
        cerr << "Ошибка открытия файла" << endl;
    }
    else
    {
        cout << "Файл открыт" << endl;
        char ch;
        while(fin.get(ch))
        {
            cout << ch;
        }
    }

    fin.close();

    return 0;
}
