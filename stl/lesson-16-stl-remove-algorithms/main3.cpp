// C++98 — std::remove и удаление хвоста строки.
#include <algorithm>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

int main(void)
{
    console::setupConsoleEncoding();

    std::string str = "Текст с  несколькими    пробелами.";
    std::cout << str << std::endl;

    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    std::cout << str << std::endl;

    return 0;
}
