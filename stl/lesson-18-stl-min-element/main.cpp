#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <algorithm>

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

template<typename T1, typename T2>
std::ostream &operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename Container>
void printContainer(
    const Container& container,
    const char* separator = ", ",
    std::ostream& os = std::cout)
{
    os << "[";
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
    os << "]";
}

template<typename T, typename Container>
void printStack(
    std::stack<T, Container> stack,
    const char* separator = ", ",
    std::ostream& os = std::cout)
{
    if (stack.empty())
    {
        os << "[]";
        return;
    }

    os << "[";
    while (!stack.empty())
    {
        os << stack.top();
        stack.pop();
        if (!stack.empty())
        {
            os << separator;
        }
    }
    os << "]";
}

template<typename T, typename Container>
void printQueue(
    std::queue<T, Container> queue,
    const char* separator = ", ",
    std::ostream& os = std::cout)
{
    if (queue.empty())
    {
        os << "[]";
        return;
    }

    os << "[";
    while (!queue.empty())
    {
        os << queue.front();
        queue.pop();
        if (!queue.empty())
        {
            os << separator;
        }
    }
    os << "]";
}

template<typename T, typename Container, typename Compare>
void printPriorityQueue(
    std::priority_queue<T, Container, Compare> pq,
    const char* separator = ", ",
    std::ostream& os = std::cout)
{
    if (pq.empty())
    {
        os << "[]";
        return;
    }

    os << "[";
    while (!pq.empty())
    {
        os << pq.top();
        pq.pop();
        if (!pq.empty())
        {
            os << separator;
        }
    }
    os << "]";
}

int main(void)
{
    setupConsoleEncoding();

    std::vector<int> vector1{12, 43, 4, 33, 9, 7, 2, 4, 9};
    printContainer(vector1);
    std::cout << "\nsize = " << vector1.size() << std::endl;

    // max_element(first, last)
    auto result = min_element(vector1.begin(), vector1.end());
    if (result != vector1.end())
    {
        std::cout << "min = " << *result << std::endl;
    }
    else
    {
        std::cout << "Максимальный элемент не определён" << std::endl;
    }
    std::cout << std::endl;

    //-------------------------------------------------------

    std::list<int> list1{3, -5, 0, 10, -7, 55, 38};
    printContainer(list1);
    std::cout << "\nsize = " << list1.size() << std::endl;

    auto result2 = min_element(list1.begin(), list1.end());
    if (result2 != list1.end())
    {
        std::cout << "min = " << *result2 << std::endl;
    }
    else
    {
        std::cout << "Максимальный элемент не определён" << std::endl;
    }
    std::cout << std::endl;

    //-------------------------------------------------------

    constexpr int SIZE = 7;
    int arr[SIZE]{54, 77, 12, 6, 54, 2, 10};
    printContainer(arr);
    std::cout << "\nsize = " << SIZE << std::endl;

    auto result3 = std::min_element(arr, arr + SIZE);
    if (result3 != arr + SIZE)
    {
        std::cout << "min = " << *result3 << std::endl;
    }
    else
    {
        std::cout << "Максимальный элемент не определён" << std::endl;
    }
    std::cout << std::endl;

    //========================================================

    std::vector<int> vector2{12, 43, 4, 33, 9, 7, 2, 4, 9};
    printContainer(vector2);
    std::cout << "\nsize = " << vector2.size() << std::endl;

    // minmax_element(first, last)
    auto result4 = minmax_element(vector2.begin(), vector2.end());
    if (result4.first != vector2.end())
    {
        std::cout << "min = " << *result4.first << std::endl;
    }
    if (result4.second != vector2.end())
    {
        std::cout << "max = " << *result4.second << std::endl;
    }

    return 0;
}
