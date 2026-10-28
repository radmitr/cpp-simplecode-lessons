#include <iostream>
#include <algorithm>
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

    std::string str = "Текст с  несколькими    пробелами.";
    std::cout << str << std::endl;

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    std::cout << str << std::endl;

    return 0;
}
