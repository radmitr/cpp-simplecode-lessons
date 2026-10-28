#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <stack>
#include <queue>
#include <algorithm>
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

class Person
{
public:
    static constexpr double PASSING_SCORE = 180.0;

    Person(std::string name, double score)
    {
        this->name = name;
        this->score = score;
    }

    bool operator()(const Person& p) const
    {
        return p.score > PASSING_SCORE;
    }

    std::string getName() const { return name; }
    double getScore() const { return score; }

private:
    std::string name;
    double score;
};

int main(void)
{
    setupConsoleEncoding();

    std::vector<Person> people = {
        Person("Вася", 181),
        Person("Петя", 30),
        Person("Маша", 179),
        Person("Даша", 200),
        Person("Катя", 198),
        Person("Андрей", 181),
        Person("Сергей", 50),
        Person("Иван", 150),
        Person("Иван", 150),
        Person("Петя", 30)
    };

    for (auto person : people)
    {
        std::cout << "Имя:\t" << person.getName() << "\tбаллы:\t" << person.getScore() << std::endl;
    }
    std::cout << std::endl;

    sort(people.begin(), people.end(), [](const Person& p1, const Person& p2) {
        return p1.getName() < p2.getName();
    });

    for (auto person : people)
    {
        std::cout << "Имя:\t" << person.getName() << "\tбаллы:\t" << person.getScore() << std::endl;
    }
    std::cout << std::endl;

    std::sort(people.begin(), people.end(), [](const Person& p1, const Person& p2) {
        return p1.getScore() > p2.getScore();
    });

    for (auto person : people)
    {
        std::cout << "Имя:\t" << person.getName() << "\tбаллы:\t" << person.getScore() << std::endl;
    }
    std::cout << std::endl;

    return 0;
}
