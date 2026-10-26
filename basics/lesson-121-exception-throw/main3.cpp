#include <iostream>
#include <fstream>

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
    cout << "value = " << value << endl;
}

int main(void)
{
    setupConsoleEncoding();

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
