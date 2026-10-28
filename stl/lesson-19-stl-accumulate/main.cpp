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

    std::vector<int> v{2, 3, 4};
    printContainer(v);
    std::cout << "\nsize = " << v.size() << std::endl;

    // accumulate(first, last, init)
    auto result = accumulate(v.begin(), v.end(), 0);
    std::cout << "sum = " << result << std::endl;

    auto result2 = accumulate(v.begin(), v.end(), 10);
    std::cout << "sum = " << result2 << std::endl;
    std::cout << std::endl;

    //----------------------------------------------------------------

    int arr[]{2, 3, 4, 5, 7, 10};
    printContainer(arr);
    std::cout << "\nsize = " << sizeof(arr) / sizeof(*arr) << std::endl;

    // begin(..), end(..)
    auto result3 = std::accumulate(std::begin(arr), std::end(arr), 0);
    std::cout << "sum = " << result3 << std::endl;

    // accumulate(first, last, init, binary_op)
    auto result4 = std::accumulate(std::begin(arr), std::end(arr), 1, [](const int a, const int b) {
        return a * b;
    });
    std::cout << "prod = " << result4 << std::endl;

    auto result5 = std::accumulate(std::begin(arr), std::end(arr), 0, [](const int a, const int b) {
        if (b % 2 == 0)
        {
            return a + b;
        }
        return a;
    });
    std::cout << "sum_odd = " << result5 << std::endl;

    // next(x, n = 1)
    std::string result6 = std::accumulate(
        std::next(std::begin(arr)),
        std::end(arr),
        std::to_string(arr[0]),
        [](const std::string& acc, const int value) {
            return acc + '-' + std::to_string(value);
        }
    );
    std::cout << "str = " << result6 << std::endl;

    // без next(..) и с string{}
    std::string result7 = std::accumulate(
        std::begin(arr),
        std::end(arr),
        std::string{},
        [](const std::string& acc, const int value) {
            return acc.empty() ? std::to_string(value) : acc + '-' + std::to_string(value);
        }
    );
    std::cout << "str = " << result7 << std::endl;

    return 0;
}
