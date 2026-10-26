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
