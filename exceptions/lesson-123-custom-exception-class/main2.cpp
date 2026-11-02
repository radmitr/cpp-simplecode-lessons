// C++98 — пользовательские классы исключений.
#include <iostream>
#include <stdexcept>

#include "../../common/console.hpp"

using namespace std;

class MyException : public invalid_argument
{
public:
    MyException(const char* msg, int dataState) : invalid_argument(msg)
    {
        this->dataState = dataState;
    }

    int getDataState()
    {
        return dataState;
    }
private:
    int dataState;
};

void foo(int value)
{
    if (value < 0)
    {
        throw invalid_argument("число меньше нуля!!!");
    }

    if (value == 1)
    {
        throw MyException("число = 1", value);
    }

    cout << "value = " << value << endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    try
    {
        //foo(-55);
        foo(1);
    }
    catch(MyException& e)
    {
        cerr << "Мы поймали " << e.what() << endl;
        cout << "Состояние данных " << e.getDataState() << endl;
    }
    catch(exception& e)
    {
        cerr << "Мы поймали " << e.what() << endl;
    }

    return 0;
}
