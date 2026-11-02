// C++98 — пользовательские классы исключений.
#include <iostream>
#include <stdexcept>

#include "../../common/console.hpp"

using namespace std;

class MyException
{
public:
private:
};

void foo(int value)
{
    if (value < 0)
    {
        throw "число меньше нуля!!!";
    }

    if (value == 0)
    {
        throw invalid_argument("число равное нулю!!!");
    }

    if (value == 1)
    {
        throw MyException();
    }

    cout << "value = " << value << endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    try
    {
        //foo(-55);
        //foo(0);
        foo(1);
    }
    catch(const char* e)
    {
        cerr << "Блок 1 Мы поймали " << e << endl;
    }
    catch(const exception& e)
    {
        cerr << "Блок 2 Мы поймали " << e.what() << endl;
    }
    catch(MyException& e)
    {
        cerr << "Блок 3 Мы поймали " << endl;
    }

    return 0;
}
