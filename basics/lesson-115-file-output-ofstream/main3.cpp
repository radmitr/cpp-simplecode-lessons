#include <iostream>
#include <string>
#include <fstream>
#include <system_error>

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
    setupConsoleEncoding();

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
