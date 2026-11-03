// C++98 — запись в файл через std::ofstream; C++11 — = delete и = default.
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <system_error>

#include "../../common/console.hpp"

using namespace std;

class FileWriter
{
private:
    ofstream file;
    string filename;

public:
    explicit FileWriter(const string& path) : filename(path)
    {
        file.open(path);
        if (!file.is_open())
        {
            throw runtime_error("Не удалось открыть файл: " + path);
        }
    }

    ~FileWriter()
    {
        if (file.is_open())
        {
            file.close();
        }
    }

    void write(const string& data)
    {
        file << data;
        if (file.fail())
        {
            throw runtime_error("Ошибка записи в файл");
        }
    }

    // Запрещаем копирование
    FileWriter(const FileWriter&) = delete;
    FileWriter& operator=(const FileWriter&) = delete;
};

int main()
{
    console::setupConsoleEncoding();

    try
    {
        FileWriter writer("myFile.txt");
        writer.write("Это наши данные\n");
        cout << "Файл успешно создан!" << endl;
    }
    catch (const exception& e)
    {
        cerr << "Ошибка: " << e.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
