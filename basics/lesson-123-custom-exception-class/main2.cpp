#include <iostream>
#include <stdexcept>

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
    setupConsoleEncoding();

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
