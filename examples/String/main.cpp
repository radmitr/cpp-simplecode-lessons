// C++98 — собственный строковый класс и перегрузка операторов.
// C++11 — перемещение и noexcept в String.hpp.
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../../common/console.hpp"
#include "String.hpp"

int main(void)
{
    console::setupConsoleEncoding();

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
