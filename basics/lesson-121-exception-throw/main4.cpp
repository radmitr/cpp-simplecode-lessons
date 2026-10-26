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
        //throw exception("число меньше нуля!!!"); // no instance of constructor "std::exception::exception" matches the argument list
        //throw runtime_error("число меньше нуля!!!");
        throw invalid_argument("число меньше нуля!!!");
    }
    cout << "value = " << value << endl;
}

int main(void)
{
    setupConsoleEncoding();

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
