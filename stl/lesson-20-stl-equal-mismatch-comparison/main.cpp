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

    int arr[]{10, 3, 4, 5, 7, 11};
    printContainer(arr);
    std::cout << std::endl;

    int arr2[]{10, 3, 4, 5, 7, 11, 1};
    printContainer(arr2);
    std::cout << std::endl;

    // equal(first1, last1, first2)
    bool result = std::equal(std::begin(arr), std::end(arr), std::begin(arr2));
    std::cout << "equal: " << result << std::endl;

    bool result2 = std::equal(std::begin(arr), std::end(arr), std::begin(arr2), std::end(arr2));
    std::cout << "equal: " << result2 << std::endl;
    std::cout << std::endl;

    //--------------------------------------------------------

    std::vector<int> v{10, 3, 4, 5, 7, 11};
    printContainer(v);
    std::cout << std::endl;

    std::vector<int> v2{10, 3, 4, 5, 7, 11};
    printContainer(v2);
    std::cout << std::endl;

    std::list<int> list1{10, 3, 4, 5, 7, 11};
    printContainer(list1);
    std::cout << std::endl;

    bool result3 = std::equal(std::begin(arr), std::end(arr), std::begin(v), std::end(v));
    std::cout << "equal: " << result3 << std::endl;

    bool result4 = std::equal(std::begin(v), std::end(v), std::begin(v2), std::end(v2));
    std::cout << "equal: " << result4 << std::endl;

    bool result5 = std::equal(std::begin(v), std::end(v), std::begin(list1), std::end(list1));
    std::cout << "equal: " << result5 << std::endl;
    std::cout << std::endl;

    //--------------------------------------------------------

    int arr3[]{11, 3, 4, 5, 7, 10};
    printContainer(arr3);
    std::cout << std::endl;

    int arr4[]{10, 3, 4, 5, 7, 11};
    printContainer(arr4);
    std::cout << std::endl;

    std::sort(std::begin(arr3), std::end(arr3));
    std::sort(std::begin(arr4), std::end(arr4));

    bool result6 = std::equal(std::begin(arr3), std::end(arr3), std::begin(arr4), std::end(arr4));
    std::cout << "equal: " << result6 << std::endl;
    std::cout << std::endl;

    //--------------------------------------------------------

    std::vector<int> v3{11, 2, 4, 5, 7, 11};
    printContainer(v3);
    std::cout << std::endl;

    std::vector<int> v4{11, 3, 4, 5, 7, 11};
    printContainer(v4);
    std::cout << std::endl;

    auto result7 = std::mismatch(std::begin(v3), std::end(v3), std::begin(v4), std::end(v4));
    if (result7.first == v3.end() && result7.second == v4.end())
    {
        std::cout << "match" << std::endl;
    }
    else
    {
        std::cout << "mismatch: " << *result7.first << " != " << *result7.second << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
