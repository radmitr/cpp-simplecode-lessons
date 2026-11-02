// C++98 — указатели на функции.
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

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
    console::setupConsoleEncoding();

    showInfo(getDataFromDB);

    return 0;
}
