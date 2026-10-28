#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

// using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
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

    //--------------------------------------------------

    std::queue<int> queue1;

    std::cout << "--- queue -------------------------\n" << std::endl;

    // push(..)
    queue1.push(45);
    queue1.push(23);
    queue1.push(81);
    queue1.push(10);
    printQueue(queue1);
    std::cout << std::endl;

    // front(), back(), size()
    std::cout << "front = " << queue1.front() << std::endl;
    std::cout << "back = " << queue1.back() << std::endl;
    std::cout << "size = " << queue1.size() << std::endl;
    std::cout << std::endl;

    // pop()
    std::cout << "pop\n" << std::endl;
    queue1.pop();
    printQueue(queue1);
    std::cout << std::endl;
    std::cout << "front = " << queue1.front() << std::endl;
    std::cout << "back = " << queue1.back() << std::endl;
    std::cout << "size = " << queue1.size() << std::endl;
    std::cout << std::endl;

    // empty()
    while (!queue1.empty())
    {
        std::cout << "pop\n" << std::endl;
        queue1.pop();
        printQueue(queue1);
        std::cout << std::endl;
        if (queue1.size() > 0)
        {
            std::cout << "front = " << queue1.front() << std::endl;
            std::cout << "back = " << queue1.back() << std::endl;
        }
        std::cout << "size = " << queue1.size() << std::endl;
        std::cout << std::endl;
    }

    //--------------------------------------------------

    std::queue<int, std::list<int>> queue2;

    std::cout << "--- queue<int, list<int>> -------------------------\n" << std::endl;

    // push(..)
    queue2.push(45);
    queue2.push(23);
    queue2.push(81);
    queue2.push(10);
    printQueue(queue2);
    std::cout << std::endl;

    // front(), back(), size()
    std::cout << "front = " << queue2.front() << std::endl;
    std::cout << "back = " << queue2.back() << std::endl;
    std::cout << "size = " << queue2.size() << std::endl;
    std::cout << std::endl;

    // pop()
    std::cout << "pop\n" << std::endl;
    queue2.pop();
    printQueue(queue2);
    std::cout << std::endl;
    std::cout << "front = " << queue2.front() << std::endl;
    std::cout << "back = " << queue2.back() << std::endl;
    std::cout << "size = " << queue2.size() << std::endl;
    std::cout << std::endl;

    // empty()
    while (!queue2.empty())
    {
        std::cout << "pop\n" << std::endl;
        queue2.pop();
        printQueue(queue2);
        std::cout << std::endl;
        if (queue2.size() > 0)
        {
            std::cout << "front = " << queue2.front() << std::endl;
            std::cout << "back = " << queue2.back() << std::endl;
        }
        std::cout << "size = " << queue2.size() << std::endl;
        std::cout << std::endl;
    }

    //--------------------------------------------------

    // 'class std::vector<int>' has no member named 'pop_front'
    //std::queue<int, std::vector<int>> queue3;

    //--------------------------------------------------

    std::priority_queue<int> priorityQueue;

    std::cout << "--- priority_queue -------------------------\n" << std::endl;

    // push(..)
    priorityQueue.push(45);
    priorityQueue.push(10);
    priorityQueue.push(81);
    priorityQueue.push(23);
    printPriorityQueue(priorityQueue);
    std::cout << std::endl;

    // top(), back(), size()
    std::cout << "top = " << priorityQueue.top() << std::endl;
    std::cout << "size = " << priorityQueue.size() << std::endl;
    std::cout << std::endl;

    // pop()
    std::cout << "pop\n" << std::endl;
    priorityQueue.pop();
    printPriorityQueue(priorityQueue);
    std::cout << std::endl;
    std::cout << "top = " << priorityQueue.top() << std::endl;
    std::cout << "size = " << priorityQueue.size() << std::endl;
    std::cout << std::endl;

    // empty()
    while (!priorityQueue.empty())
    {
        std::cout << "pop\n" << std::endl;
        priorityQueue.pop();
        printPriorityQueue(priorityQueue);
        std::cout << std::endl;
        if (priorityQueue.size() > 0)
        {
            std::cout << "top = " << priorityQueue.top() << std::endl;
        }
        std::cout << "size = " << priorityQueue.size() << std::endl;
        std::cout << std::endl;
    }

    //--------------------------------------------------

    std::priority_queue<int, std::deque<int>, std::greater<int>> minPriorityQueue;

    std::cout << "--- priority_queue<int, deque<int>, greater<int>> -------------------------\n" << std::endl;

    // push(..)
    minPriorityQueue.push(45);
    minPriorityQueue.push(10);
    minPriorityQueue.push(81);
    minPriorityQueue.push(23);
    printPriorityQueue(minPriorityQueue);
    std::cout << std::endl;

    // top(), back(), size()
    std::cout << "top = " << minPriorityQueue.top() << std::endl;
    std::cout << "size = " << minPriorityQueue.size() << std::endl;
    std::cout << std::endl;

    // pop()
    std::cout << "pop\n" << std::endl;
    minPriorityQueue.pop();
    printPriorityQueue(priorityQueue);
    std::cout << std::endl;
    std::cout << "top = " << minPriorityQueue.top() << std::endl;
    std::cout << "size = " << minPriorityQueue.size() << std::endl;
    std::cout << std::endl;

    // empty()
    while (!minPriorityQueue.empty())
    {
        std::cout << "pop\n" << std::endl;
        minPriorityQueue.pop();
        printPriorityQueue(minPriorityQueue);
        std::cout << std::endl;
        if (minPriorityQueue.size() > 0)
        {
            std::cout << "top = " << minPriorityQueue.top() << std::endl;
        }
        std::cout << "size = " << minPriorityQueue.size() << std::endl;
        std::cout << std::endl;
    }

    //--------------------------------------------------

    // class "std::priority_queue<int, std::__cxx11::list<int, std::allocator<int>>, std::less<int>>" has no member "front"
    // class "std::priority_queue<int, std::__cxx11::list<int, std::allocator<int>>, std::less<int>>" has no member "back"
    //std::priority_queue<int, std::list<int>> priorityQueue2;

    //--------------------------------------------------

    std::priority_queue<int, std::vector<int>> priorityQueue3;

    //--------------------------------------------------

    std::priority_queue<int, std::deque<int>> priorityQueue4;

    return 0;
}
