// C++11 — std::array и цикл for по диапазону.
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>

#include "../../common/console.hpp"

//using namespace std;

template<typename T, std::size_t N>
void printArray(const std::array<T, N>& arr, const char* sep = "\n")
{
    for (const auto& val : arr)
    {
        std::cout << val << sep;
    }
    std::cout << std::flush;
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
    console::setupConsoleEncoding();

    std::array<int, 5> arr{4, 33, 96, 11, 73};

    printArray(arr);
    std::cout << std::endl;

    printContainer(arr);
    std::cout << std::endl;

    // [i]
    //std::cout << arr[111] << std::endl; //Assertion '__n < this->size()' failed

    // at(..)
    try
    {
        std::cout << arr.at(111) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n'; // array::at: __n (which is 111) >= _Nm (which is 5)
    }
    std::cout << std::endl;

    // size()
    for (size_t i = 0; i < arr.size(); i++)
    {
        std::cout << arr[i] << std::endl;
    }
    std::cout << std::endl;

    // range based for
    for (auto&& val : arr)
    {
        std::cout << val << std::endl;
    }
    std::cout << std::endl;

    // front(), back()
    std::cout << arr.front() << std::endl;
    std::cout << arr.back() << std::endl;
    std::cout << std::endl;

    // fill(..)
    arr.fill(-1);
    printContainer(arr);
    std::cout << std::endl;

    return 0;
}
