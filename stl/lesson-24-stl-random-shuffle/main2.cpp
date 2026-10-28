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
#include <memory>

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

class IAction
{
public:
    virtual ~IAction() = default;
    virtual void act() = 0;
};

class CatAction : public IAction
{
    virtual void act() override
    {
        std::cout << "Гладим кота" << std::endl;
    }
};

class TeaAction : public IAction
{
    virtual void act() override
    {
        std::cout << "Пьём чай" << std::endl;
    }
};

class DogAction : public IAction
{
    virtual void act() override
    {
        std::cout << "Гуляем с собакой" << std::endl;
    }
};

class SleepAction : public IAction
{
    virtual void act() override
    {
        std::cout << "Спим" << std::endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    std::random_device rd;
    std::mt19937 g(rd());

    CatAction catAction;
    TeaAction teaAction;
    DogAction dogAction;
    SleepAction sleepAction;

    IAction* arr[] = {
        &catAction,
        &teaAction,
        &dogAction,
        &sleepAction
    };

    for (const auto& action : arr)
    {
        action->act();
    }
    std::cout << std::endl;

    std::shuffle(std::begin(arr), std::end(arr), g);

    for (const auto& action : arr)
    {
        action->act();
    }
    std::cout << "-----------------------------------------" << std::endl;

    IAction* arr2[] = {
        new CatAction(),
        new TeaAction(),
        new DogAction(),
        new SleepAction()
    };

    for (auto& action : arr2)
    {
        action->act();
    }
    std::cout << std::endl;

    std::shuffle(std::begin(arr2), std::end(arr2), g);

    for (auto& action : arr2)
    {
        action->act();
    }

    for (auto& action : arr2)
    {
        delete action;
    }
    std::cout << "-----------------------------------------" << std::endl;

    std::unique_ptr<IAction> arr3[] = {
        std::make_unique<CatAction>(),
        std::make_unique<TeaAction>(),
        std::make_unique<DogAction>(),
        std::make_unique<SleepAction>()
    };

    for (const auto& action : arr3)
    {
        action->act();
    }
    std::cout << std::endl;

    std::shuffle(std::begin(arr3), std::end(arr3), g);

    for (const auto& action : arr3)
    {
        action->act();
    }
    std::cout << std::endl;
    std::cout << "-----------------------------------------" << std::endl;

    std::vector<std::unique_ptr<IAction>> v;
    v.reserve(4);
    v.emplace_back(std::make_unique<CatAction>());
    v.emplace_back(std::make_unique<TeaAction>());
    v.emplace_back(std::make_unique<DogAction>());
    v.emplace_back(std::make_unique<SleepAction>());

    for (const auto& action : v)
    {
        action->act();
    }
    std::cout << std::endl;

    std::shuffle(std::begin(v), std::end(v), g);

    for (const auto& action : v)
    {
        action->act();
    }
    std::cout << std::endl;

    return 0;
}
