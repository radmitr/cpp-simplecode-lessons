// C++98 — throw и передача исключения обработчику.
#include <iostream>
#include <fstream>

#include "../../common/console.hpp"

using namespace std;

void foo(int value)
{
    if (value < 0)
    {
        throw "число меньше нуля!!!";
    }
    cout << "value = " << value << endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    try
    {
        foo(-55);
    }
    catch(const char* e)
    {
        cerr << "Мы поймали " << e << '\n';
    }

    return 0;
}
