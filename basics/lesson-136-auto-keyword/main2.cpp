#include <iostream>
#include <vector>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

//using namespace std;

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
