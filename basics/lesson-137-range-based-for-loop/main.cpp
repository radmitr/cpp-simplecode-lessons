#include <iostream>
#include <list>

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
