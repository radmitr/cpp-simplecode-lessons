#include <iostream>
#include <string>

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

string getDataFromDB()
{
    return "Data From DB";
}

string getDataFromWebServer()
{
    return "Data From WebServer";
}

string getDataFromAstral()
{
    return "Data From Astral";
}

void showInfo(string(*foo)())
{
    cout << foo() << endl;
}

int main(void)
{
    setupConsoleEncoding();

    showInfo(getDataFromDB);

    return 0;
}
