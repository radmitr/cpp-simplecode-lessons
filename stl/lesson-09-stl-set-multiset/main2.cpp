#include <iostream>
#include <set>

// using namespace std;

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
    setupConsoleEncoding();

    // std::multiset<int>
    std::multiset<int> multiset1{0, 1, 1, 1, 45, 45, 23, 83, 77, 1, 30, 16};
    printContainer(multiset1);
    std::cout << std::endl;

    // insert(..)
    multiset1.insert(23);
    printContainer(multiset1);
    std::cout << std::endl;

    // lower_bound(..), upper_bound(..)
    auto it1 = multiset1.lower_bound(1);
    auto it2 = multiset1.upper_bound(1);
    std::cout << "it1 (lower_bound) = " << *it1 << std::endl;
    std::cout << "it2 (upper_bound) = " << *it2 << std::endl;

    // equal_range(..)
    auto range = multiset1.equal_range(1);
    std::cout << "range = [" << *range.first << ", " << *range.second << "]" << std::endl;
    std::cout << std::endl;

    int arr[] = {10, 20, 30};
    printContainer(arr);

    return 0;
}
