#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <algorithm>
#include <numeric>
#include <string>
#include <ctime>
#include <random>

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

    srand(time(NULL));

    std::vector<int> v{1, 2, 3, 4, 5};
    printContainer(v);
    std::cout << '\n' << std::endl;

    // random_shuffle(first, last)
    std::random_shuffle(std::begin(v), std::end(v)); // is deprecated
    printContainer(v);
    std::cout << std::endl;

    std::random_shuffle(std::begin(v), std::end(v)); // is deprecated
    printContainer(v);
    std::cout << '\n' << std::endl;

    //----------------------------------------------------------

    int arr[] = {1, 2, 3, 4, 5};
    printContainer(arr);
    std::cout << '\n' << std::endl;

    std::random_shuffle(std::begin(arr), std::end(arr)); // is deprecated
    printContainer(arr);
    std::cout << std::endl;

    std::random_shuffle(std::begin(arr), std::end(arr)); // is deprecated
    printContainer(arr);
    std::cout << '\n' << std::endl;

    // Создаём генератор случайных чисел
    std::random_device rd;  // источник энтропии
    std::mt19937 g(rd());   // генератор Mersenne Twister

    // shuffle(first, last, g)
    std::shuffle(std::begin(arr), std::end(arr), g);
    printContainer(arr);
    std::cout << std::endl;

    std::shuffle(std::begin(arr), std::end(arr), g);
    printContainer(arr);
    std::cout << std::endl;

    return 0;
}
