// C++98 — throw и передача исключения обработчику.
#include <iostream>
#include <stdexcept>

#include "../../common/console.hpp"

using namespace std;

void foo(int value)
{
    if (value < 0)
    {
        //throw exception("число меньше нуля!!!"); // no instance of constructor "std::exception::exception" matches the argument list
        //throw runtime_error("число меньше нуля!!!");
        throw invalid_argument("число меньше нуля!!!");
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
    catch(const exception& e)
    {
        cerr << "Мы поймали " << e.what() << endl;
    }

    return 0;
}
