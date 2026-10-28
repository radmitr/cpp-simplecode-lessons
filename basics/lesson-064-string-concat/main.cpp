#include <iostream>
#include <cstring>

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
