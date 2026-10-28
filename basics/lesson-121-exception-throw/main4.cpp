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
