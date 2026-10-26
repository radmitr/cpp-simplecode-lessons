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
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p)
{
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template<typename Container>
void printContainer(
    const Container &container,
    const char *separator = ", ",
    std::ostream &os = std::cout)
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
    const char *separator = ", ",
    std::ostream &os = std::cout)
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
    const char *separator = ", ",
    std::ostream &os = std::cout)
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
    const char *separator = ", ",
    std::ostream &os = std::cout)
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

bool greaterThenZero(int a)
{
    return a > 0;
}

bool lessThenZero(int a)
{
    return a < 0;
}

bool equalZero(int a)
{
    return a == 0;
}

bool greater(int a, int b)
{
    return a > b;
}

bool less(int a, int b)
{
    return a < b;
}

bool equal(int a, int b)
{
    return a == b;
}

int main(void)
{
    setupConsoleEncoding();

    std::vector<int> v{12, 43, 33, 2, 9, 84, 0, 14, 23};

    printContainer(v);
    std::cout << std::endl;

    // можно без std, т.к. происходит механизм ADL (Argument-Dependent Lookup)
    sort(v.begin(), v.end());
    printContainer(v);
    std::cout << std::endl;

    // без std ошибка: identifier "sort" is undefined
    int arr[] = {3, 1, 4, 11, 34, 0, -10};
    std::sort(arr, arr + sizeof(arr)/sizeof(*arr));
    printContainer(arr);
    std::cout << std::endl;

    // унарный предикат greater
    sort(v.begin(), v.end(), greater);
    printContainer(v);
    std::cout << std::endl;

    // унарный предикат less
    sort(v.begin(), v.end(), less);
    printContainer(v);
    std::cout << std::endl;

    // стандартный функтор std::greater<..>
    std::sort(v.begin(), v.end(), std::greater<int>{});
    printContainer(v);
    std::cout << std::endl;

    // стандартный функтор std::less<..>
    std::sort(v.begin(), v.end(), std::less<void>{});
    printContainer(v);
    std::cout << std::endl;

    // анонимная функция
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });
    printContainer(v);
    std::cout << std::endl;

    // анонимная функция
    std::sort(v.begin(), v.end(), [](int a, int b) {
        return a < b;
    });
    printContainer(v);
    std::cout << std::endl;

    return 0;
}
