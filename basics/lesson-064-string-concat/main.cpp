#include <iostream>
#include <cstring>

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

    char result[255]{};
    char str1[6] = "Hello";
    char str2[255] = "World";

    cout << str1 << endl;
    cout << str2 << endl;

    strcat(result, str1);
    strcat(result, str2);

    cout << result << endl;

    return 0;
}
