// C++98 — чтение файла через std::ifstream.
#include <fstream>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

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
        char str[50];
        while(fin.getline(str, sizeof(str)))
        {
            cout << str << endl;
        }
    }

    fin.close();

    return 0;
}
