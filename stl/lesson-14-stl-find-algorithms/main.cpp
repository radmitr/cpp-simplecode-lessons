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

int main(void)
{
    setupConsoleEncoding();

    std::vector<int> v{12, 43, 33, 7, 2, 9, 84, 0, 14, 25, 11};

    printContainer(v);
    std::cout << std::endl;

    // find(begin, end, value)
    auto result = find(v.begin(), v.end(), 33);

    if (result == v.end())
    {
        std::cout << '-' << std::endl;
    }
    else
    {
        std::cout << '+' << std::endl;
    }

    //-------------------------------------------------------------------------

    std::vector<int> v2{12, 2, 84, 0, 14}; // even

    // find_if(begin, end, pred)
    auto result2 = std::find_if(v2.begin(), v2.end(), [](int a) {
        return a % 2 == 0;
    });

    if (result2 != v2.end())
    {
        std::cout << *result2 << std::endl;
    }
    else
    {
        std::cout << "Чётные числа не найдены!" << std::endl;
    }

    result2 = std::find_if(v2.begin(), v2.end(), [](int a) {
        return a % 2 != 0;
    });

    if (result2 != v2.end())
    {
        std::cout << *result2 << std::endl;
    }
    else
    {
        std::cout << "Нечётные числа не найдены!" << std::endl;
    }

    result2 = std::find_if(v2.begin(), v2.end(), [](int a) {
        return a < 0;
    });

    if (result2 != v2.end())
    {
        std::cout << *result2 << std::endl;
    }
    else
    {
        std::cout << "Числа меньше нуля не найдены!" << std::endl;
    }

    // find_if_not(begin, end, pred)
    result2 = std::find_if_not(v2.begin(), v2.end(), [](int a) {
        return a < 0;
    });

    if (result2 != v2.end())
    {
        std::cout << *result2 << std::endl;
    }
    else
    {
        std::cout << "Числа не меньше нуля не найдены!" << std::endl;
    }

    return 0;
}
