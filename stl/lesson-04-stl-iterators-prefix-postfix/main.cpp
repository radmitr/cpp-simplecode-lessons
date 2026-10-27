#include <iostream>
#include <list>

//using namespace std;

template<typename T>
void printList(const std::list<T>& lst)
{
    for (auto it = lst.cbegin(); it != lst.cend(); ++it)
    {
        std::cout << *it << std::endl;
    }
}

int main(void)
{
    std::list<int> values{10, 20, 30};
    auto it = values.begin(); // указывает на 10

    auto previous = it++;    // previous указывает на 10, it — на 20
    auto current = ++it;     // current и it указывают на 30

    std::cout << *previous << '\n'; // 10
    std::cout << *current << '\n';  // 30

    return 0;
}
