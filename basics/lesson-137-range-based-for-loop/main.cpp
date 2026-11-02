// C++11 — цикл for по диапазону.
#include <iostream>
#include <list>

#include "../../common/console.hpp"

//using namespace std;

int main(void)
{
    console::setupConsoleEncoding();

    // --- array ---
    int arr[] = {1, 56, 93, 21, 6, 78};

    // Это эксклюзивное расширение MSVC (Microsoft Visual C++)
    // for each (auto var in arr)
    // {
    //     std::cout << var << std::endl;
    // }

    for (auto var : arr)
    {
        std::cout << var << std::endl;
    }
    std::cout << std::endl;

    for (auto&& var : arr)
    {
        var = -1;
    }

    for (const auto var : arr)
    {
        std::cout << var << std::endl;
    }
    std::cout << std::endl;

    // --- list ---
    std::list<int> list1 = {3, 44, 65, 30, 2};

    for (const auto& i : list1)
    {
        std::cout << i << std::endl;
    }

    return 0;
}
