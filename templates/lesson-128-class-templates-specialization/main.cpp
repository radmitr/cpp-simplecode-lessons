// C++98 — специализация шаблонов классов.
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

    Printer<int> printer;
    printer.print(5);

    Printer<string> printer2;
    printer2.print("Hello, World!!!");

    return 0;
}
