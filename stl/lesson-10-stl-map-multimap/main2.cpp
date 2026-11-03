// C++98 — std::multimap; C++11 — auto и std::begin().
#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <utility>

#include "../../common/console.hpp"

// using namespace std;

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

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

    std::multimap<std::string, int> map1;

    map1.emplace("Петя", 3445);
    map1.emplace("Петя", 100);
    map1.emplace("Маша", 6431);
    map1.emplace("Миша", 2973);
    printContainer(map1);

    //map1["Петя"]; // no operator "[]" matches these operands
    //map1.at("Петя"); // class std::multimap has no member "at"

    return 0;
}
