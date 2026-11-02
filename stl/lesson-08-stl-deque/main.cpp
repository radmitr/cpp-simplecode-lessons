// C++98 — std::deque; C++11 — auto.
#include <iostream>
#include <deque>

#include "../../common/console.hpp"

//using namespace std;

template<typename Container>
void printContainer(const Container& container, const char* separator = "\n")
{
    auto it = container.begin();
    if (it != container.end())
    {
        std::cout << *it;
        ++it;
        for (; it != container.end(); ++it)
        {
            std::cout << separator << *it;
        }
    }
    std::cout << std::endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    // гибрид двух контейнеров: vector и list
    std::deque<int> dq{12, 44, 97};
    printContainer(dq);
    std::cout << std::endl;

    // push_back(..), push_front(..)
    dq.push_back(999);
    dq.push_front(111);
    printContainer(dq);
    std::cout << std::endl;

    // [..]
    std::cout << "dq[0] = " << dq[0] << std::endl;
    std::cout << "dq[1] = " << dq[1] << std::endl;
    //std::cout << "dq[111] = " << dq[111] << std::endl;

    // at(..)
    try
    {
        std::cout << "dq.at(111) = " << dq.at(111) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
