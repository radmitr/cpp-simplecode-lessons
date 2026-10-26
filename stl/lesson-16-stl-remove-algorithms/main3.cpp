#include <iostream>
#include <algorithm>
#include <string>

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

    std::string str = "Текст с  несколькими    пробелами.";
    std::cout << str << std::endl;

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    std::cout << str << std::endl;

    return 0;
}
