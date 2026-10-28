#include <iostream>
#include <string>

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
