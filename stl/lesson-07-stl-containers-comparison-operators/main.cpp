#include <iostream>
#include <array>

//using namespace std;

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
