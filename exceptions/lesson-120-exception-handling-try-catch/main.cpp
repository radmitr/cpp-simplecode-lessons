// C++98 — try / catch и исключения файловых потоков.
#include <iostream>
#include <string>
#include <fstream>

#include "../../common/console.hpp"

using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

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
    catch(const std::exception& e)
    {
        cerr << "Ошибка открытия файла!" << endl;
        cerr << e.what() << endl;
    }

    return 0;
}
