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

    // --- vector1 ---
    std::cout << "vector<int> vector1(20) = {0, 454, 576, 620}:" << std::endl;
    std::vector<int> vector1 = {0, 454, 576, 620};
    std::cout << "size = " << vector1.size() << std::endl;
    std::cout << "capacity = " << vector1.capacity() << '\n' << std::endl;

    std::cout << "push_back(..)...:" << std::endl;
    vector1.push_back(5);
    vector1.push_back(14);
    vector1.push_back(27);
    vector1.push_back(39);
    vector1.push_back(41);
    vector1.push_back(52);
    vector1.push_back(65);
    vector1.push_back(70);
    vector1.push_back(84);
    std::cout << "size = " << vector1.size() << std::endl;
    std::cout << "capacity = " << vector1.capacity() << '\n' << std::endl;

    std::cout << "[i]:" << std::endl;
    for (size_t i = 0; i < vector1.size(); i++)
    {
        std::cout << i << ": " << vector1[i] << std::endl;
    }
    std::cout << std::endl;

    //vector[111] = 1; // Assertion '__n < this->size()' failed.
    //std::cout << vector1[111] << std::endl; // Assertion '__n < this->size()' failed.

    //std::cout << vector1.at(111) << std::endl; // terminate called after throwing an instance of 'std::out_of_range' what():  vector::_M_range_check: __n (which is 111) >= this->size() (which is 13)

    std::cout << "at(111):" << std::endl;
    try
    {
        std::cout << vector1.at(111) << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << e.what() << '\n' << std::endl;; // vector::_M_range_check: __n (which is 111) >= this->size() (which is 13)
    }

    std::cout << "pop_back():" << std::endl;
    vector1.pop_back();
    std::cout << "size = " << vector1.size() << std::endl;
    std::cout << "capacity = " << vector1.capacity() << '\n' << std::endl;

    std::cout << "reserve(..):" << std::endl;
    vector1.reserve(100);
    std::cout << "size = " << vector1.size() << std::endl;
    std::cout << "capacity = " << vector1.capacity() << '\n' << std::endl;

    std::cout << "resize(..):" << std::endl;
    //vector1.resize(20);
    vector1.resize(20, -1);
    for (size_t i = 0; i < vector1.size(); i++)
    {
        std::cout << i << ": " << vector1[i] << std::endl;
    }
    std::cout << std::endl;
    std::cout << "size = " << vector1.size() << std::endl;
    std::cout << "capacity = " << vector1.capacity() << '\n' << std::endl;

    std::cout << "shrink_to_fit():" << std::endl;
    vector1.shrink_to_fit();
    std::cout << "size = " << vector1.size() << std::endl;
    std::cout << "capacity = " << vector1.capacity() << '\n' << std::endl;

    std::cout << "empty(): " << vector1.empty() << '\n' << std::endl;

    std::cout << "clear():" << std::endl;
    vector1.clear();
    std::cout << "size = " << vector1.size() << std::endl;
    std::cout << "capacity = " << vector1.capacity() << '\n' << std::endl;

    std::cout << "empty(): " << vector1.empty() << '\n' << std::endl;

    // --- vector2 ---
    std::cout << "vector<int> vector2(20):" << std::endl;
    std::vector<int> vector2(20);
    for (size_t i = 0; i < vector2.size(); i++)
    {
        std::cout << i << ": " << vector2[i] << std::endl;
    }
    std::cout << "size = " << vector2.size() << std::endl;
    std::cout << "capacity = " << vector2.capacity() << '\n' << std::endl;

    // --- vector3 ---
    std::cout << "vector<int> vector3(20, 55):" << std::endl;
    std::vector<int> vector3(20, 55);
    for (size_t i = 0; i < vector3.size(); i++)
    {
        std::cout << i << ": " << vector3[i] << std::endl;
    }
    std::cout << "size = " << vector3.size() << std::endl;
    std::cout << "capacity = " << vector3.capacity() << '\n' << std::endl;

    return 0;
}
