#include <iostream>
#include <stdexcept>

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
