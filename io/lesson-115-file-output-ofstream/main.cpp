// C++98 — запись в файл через std::ofstream.
#include <iostream>
#include <string>
#include <fstream>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

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
