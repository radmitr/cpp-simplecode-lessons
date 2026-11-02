// C++11 — вывод типа через auto.
#include <iostream>
#include <vector>

#include "../../common/console.hpp"

//using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    std::vector<int> vector1 = {11, 46, 9};

    std::vector<int>::iterator it = vector1.begin();

    auto it2 = vector1.begin();

    for (std::vector<int>::iterator it = vector1.begin(); it != vector1.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    for (auto it = vector1.begin(); it != vector1.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    return 0;
}
