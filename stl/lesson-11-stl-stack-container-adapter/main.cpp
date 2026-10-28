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

int main(void)
{
    setupConsoleEncoding();

    std::stack<int> stack1;

    // push(..), emplace(..)
    stack1.push(10);
    stack1.push(23);
    stack1.push(35);
    stack1.push(47);
    stack1.emplace(51);
    printStack(stack1);
    std::cout << "size = " << stack1.size() << std::endl;
    std::cout << std::endl;

    // top()
    std::cout << stack1.top() << std::endl;
    std::cout << std::endl;

    // pop()
    stack1.pop();
    printStack(stack1);
    std::cout << std::endl;

    // empty()
    while (!stack1.empty())
    {
        std::cout << stack1.top() << std::endl;
        stack1.pop();
    }
    std::cout << "--------------------------------" << std::endl;

    // ------------------------------------------------------------------

    // stack<.., list<..>>
    std::stack<int, std::list<int>> stack2;

    stack2.push(10);
    stack2.push(23);
    stack2.push(35);
    stack2.push(47);
    stack2.emplace(51);
    printStack(stack2);
    std::cout << "size = " << stack2.size() << std::endl;
    std::cout << std::endl;

    // top()
    std::cout << stack2.top() << std::endl;
    std::cout << std::endl;

    // pop()
    stack2.pop();
    printStack(stack2);
    std::cout << std::endl;

    // empty()
    while (!stack2.empty())
    {
        std::cout << stack2.top() << std::endl;
        stack2.pop();
    }
    std::cout << "--------------------------------" << std::endl;

    // ------------------------------------------------------------------

    // stack<.., vector<..>>
    std::stack<int, std::vector<int>> stack3;

    stack3.push(10);
    stack3.push(23);
    stack3.push(35);
    stack3.push(47);
    stack3.emplace(51);
    printStack(stack3);
    std::cout << "size = " << stack3.size() << std::endl;
    std::cout << std::endl;

    // top()
    std::cout << stack3.top() << std::endl;
    std::cout << std::endl;

    // pop()
    stack3.pop();
    printStack(stack3);
    std::cout << std::endl;

    // empty()
    while (!stack3.empty())
    {
        std::cout << stack3.top() << std::endl;
        stack3.pop();
    }
    std::cout << "--------------------------------" << std::endl;

    return 0;
}
