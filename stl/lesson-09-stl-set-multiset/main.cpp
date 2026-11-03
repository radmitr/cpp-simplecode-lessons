// C++98 — std::set; C++11 — auto и std::begin().
#include <iostream>
#include <iterator>
#include <set>

#include "../../common/console.hpp"

// using namespace std;

template<typename Container>
void printContainer(
    const Container &container,
    const char *separator = "\n",
    std::ostream &os = std::cout)
{
    auto it = std::begin(container);
    if (it != std::end(container))
    {
        os << *it;
        ++it;
        for (; it != std::end(container); ++it)
        {
            os << separator << *it;
        }
    }
    os << std::endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    std::set<int> set1{5, 23, 76, 11};
    printContainer(set1);
    std::cout << std::endl;

    // insert(..)
    set1.insert(50);
    set1.insert(2);
    set1.insert(100);
    printContainer(set1);
    std::cout << std::endl;

    set1.insert(2);
    set1.insert(2);
    set1.insert(2);
    set1.insert(2);
    printContainer(set1);
    std::cout << std::endl;

    // find(..)
    auto it = set1.find(76);
    std::cout << (it == set1.end()) << std::endl;
    auto it2 = set1.find(77);
    std::cout << (it2 == set1.end()) << std::endl;
    std::cout << std::endl;

    std::cout << "Введите число:" << std::endl;
    int value;
    std::cin >> value;
    if (set1.find(value) != set1.end())
    {
        std::cout << "Число "<< value << " найдено" << std::endl;
    }
    else
    {
        std::cout << "Число "<< value << " отсутствует" << std::endl;
    }

    // erase(..)
    auto result = set1.erase(5);
    std::cout << "result = " << result << std::endl;
    printContainer(set1);
    std::cout << std::endl;

    result = set1.erase(4444);
    std::cout << "result = " << result << std::endl;

    // std::pair<iterator, bool> resultPair = set1.insert(6)
    auto resultPair = set1.insert(6);
    std::cout << "resultPair = [" << *resultPair.first << ", " << resultPair.second << "]" << std::endl;
    printContainer(set1);
    std::cout << std::endl;

    resultPair = set1.insert(76);
    std::cout << "resultPair = [" << *resultPair.first << ", " << resultPair.second << "]" << std::endl;
    printContainer(set1);
    std::cout << std::endl;

    return 0;
}
