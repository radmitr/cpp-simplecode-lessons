#include "String.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <sstream>

int main(void)
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
#endif

    std::cout << "---------START---------" << std::endl;
    String s1("Hello");
    String s2(", world!");

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;

    //String s3 = s1 + s2;
    String s3;
    s3 = s1 + s2;

    std::cout << "s3: " << s3 << std::endl;

    std::cout << "----------END----------" << std::endl;
    return 0;
}
