#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <string>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
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

    std::vector<int> v{1, 2, 2, 2, 5, 4, 4};
    printContainer(v);
    std::cout << std::endl;

    // unique(first, last)
    auto result = std::unique(std::begin(v), std::end(v));
    printContainer(v);
    std::cout << std::endl;

    for_each(begin(v), result, [](const int& a) {
        std::cout << a << std::endl;
    });

    v.erase(result, v.end());
    printContainer(v);
    std::cout << '\n' << std::endl;

    //----------------------------------------------------------

    std::vector<int> v1{0, 1, 2, 2, 2, 3, 3, 5, 4, 4, 7};
    std::list<int> v2;

    // unique_copy(first, last, result)
    std::unique_copy(v1.begin(), v1.end(), std::back_inserter(v2));
    printContainer(v2);
    std::cout << std::endl;

    return 0;
}
