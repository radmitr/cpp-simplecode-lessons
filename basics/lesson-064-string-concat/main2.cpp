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

int main(void)
{
    setupConsoleEncoding();

    string result;
    string str1 = "Hello";
    string str2 = "World";
    string str3 = "!!!";

    result = str1 + ", " + str2 + str3;

    cout << result << endl;

    return 0;
}
