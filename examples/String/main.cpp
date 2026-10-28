#include "String.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <sstream>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

int main(void)
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
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
