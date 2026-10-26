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
        throw value;
    }

    cout << "value = " << value << endl;
}

int main(void)
{
    setupConsoleEncoding();

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
    // catch(const int e)
    // {
    //     cerr << "Блок 3 Мы поймали " << e << endl;
    // }
    catch(...)
    {
        cerr << "Что-то пошло не так!!!" << endl;
    }

    return 0;
}
