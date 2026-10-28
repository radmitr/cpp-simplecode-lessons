#include <iostream>
#include <string>

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
