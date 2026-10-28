#include <iostream>
#include <array>

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

template<typename Container>
void printContainer(const Container& container, const char* separator = "\n")
{
    for (const auto& val : container)
    {
        std::cout << val << separator;
    }
    std::cout << std::flush;
}

int main(void)
{
    setupConsoleEncoding();

    std::array<int, 5> arr{4, 33, 96, 11, 73};
    std::array<int, 5> arr2{4, 33, 96, 11, 73};
    std::array<int, 5> arr3{4, 33, 96, 11, 999};
    std::array<int, 5> arr4{4, 33, 96, 11};

    bool result = arr == arr2;
    std::cout << result << std::endl;

    bool result2 = arr2 == arr3;
    std::cout << result2 << '\n' << std::endl;

    std::cout << (arr > arr2) << std::endl;
    std::cout << (arr2 > arr) << '\n' << std::endl;

    std::cout << (arr3 > arr2) << '\n' << std::endl;

    std::cout << (arr > arr4) << std::endl;

    return 0;
}
