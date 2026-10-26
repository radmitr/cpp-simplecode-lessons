#include <iostream>
#include <string>

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

template<class T>
class Printer
{
public:
    void print(T value)
    {
        cout << value << endl;
    }
};

template<>
class Printer<string>
{
public:
    void print(string value)
    {
        cout << "___" << value << "___" << endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    Printer<int> printer;
    printer.print(5);

    Printer<string> printer2;
    printer2.print("Hello, World!!!");

    return 0;
}
