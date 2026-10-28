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

    Person(std::string name, double score, int age)
    {
        this->name = name;
        this->score = score;
        this->age = age;
    }

    bool operator()(const Person& p) const
    {
        return p.score > PASSING_SCORE;
    }

    std::string getName() const { return name; }
    double getScore() const { return score; }
    double getAge() const { return age; }

private:
    std::string name;
    double score;
    int age;
};

int main(void)
{
    setupConsoleEncoding();

    std::vector<Person> people = {
        Person("Вася", 181, 17),
        Person("Петя", 30, 23),
        Person("Маша", 179, 18),
        Person("Даша", 200, 50),
        Person("Катя", 198, 19),
        Person("Андрей", 181, 33),
        Person("Андрей", 190, 45),
        Person("Сергей", 50, 20),
        Person("Серж", 50, 60),
        Person("Серж", 180, 40),
        Person("Иван", 150, 18),
        Person("Иван", 159, 18),
        Person("Петя", 30, 17)
    };

    for (auto person : people)
    {
        std::cout << "Имя:\t" << person.getName() << "\tбаллы:\t" << person.getScore() << "\tвозраст:\t" << person.getAge() << std::endl;
    }
    std::cout << "Всего элементов: " << people.size() << std::endl;
    std::cout << std::endl;

    //--------------------------------------------------------------

    std::vector<Person> result;

    // copy(first, last, result)
    copy(people.begin(), people.end(), std::back_inserter(result));

    for (auto person : result)
    {
        std::cout << "Имя:\t" << person.getName() << "\tбаллы:\t" << person.getScore() << "\tвозраст:\t" << person.getAge() << std::endl;
    }
    std::cout << "Всего элементов: " << result.size() << std::endl;
    std::cout << std::endl;

    //--------------------------------------------------------------

    std::vector<Person> result2;

    // copy_if(first, _last, result, pred)
    copy_if(people.begin(), people.end(), std::back_inserter(result2), [](const Person& person) {
        return person.getName() == "Иван";
    });

    if (result2.size() > 0)
    {
        for (auto &&i : result2)
        {
            std::cout << "Имя:\t" << i.getName() << "\tбаллы:\t" << i.getScore() << "\tвозраст:\t" << i.getAge() << std::endl;
        }
    }
    else
    {
        std::cout << "Студент(ка) не найден(а)!" << std::endl;
    }
    std::cout << "Всего элементов: " << result2.size() << std::endl;
    std::cout << std::endl;

    //-----------------------

    std::vector<Person> result3;

    copy_if(people.begin(), people.end(), std::back_inserter(result3), [](const Person& person) {
        return person.getScore() < 100;
    });

    if (result3.size() > 0)
    {
        for (auto &&i : result3)
        {
            std::cout << "Имя:\t" << i.getName() << "\tбаллы:\t" << i.getScore() << "\tвозраст:\t" << i.getAge() << std::endl;
        }
    }
    else
    {
        std::cout << "Студент(ка) не найден(а)!" << std::endl;
    }
    std::cout << "Всего элементов: " << result3.size() << std::endl;
    std::cout << std::endl;

    //-----------------------

    std::vector<Person> result4;

    copy_if(people.begin(), people.end(), std::back_inserter(result4), [](const Person& person) {
        return person.getAge() > 25;
    });

    sort(result4.begin(), result4.end(), [](const Person& p1, const Person& p2) {
        return p1.getAge() > p2.getAge();
    });

    if (result4.size() > 0)
    {
        for (auto &&i : result4)
        {
            std::cout << "Имя:\t" << i.getName() << "\tбаллы:\t" << i.getScore() << "\tвозраст:\t" << i.getAge() << std::endl;
        }
    }
    else
    {
        std::cout << "Студент(ка) не найден(а)!" << std::endl;
    }
    std::cout << "Всего элементов: " << result4.size() << std::endl;
    std::cout << std::endl;

    //-----------------------

    std::vector<Person> result5;

    copy_if(people.begin(), people.end(), std::back_inserter(result5), [](const Person& person) {
        return person.getAge() > 25 && person.getScore() > 140;
    });

    if (result5.size() > 0)
    {
        for (auto &&i : result5)
        {
            std::cout << "Имя:\t" << i.getName() << "\tбаллы:\t" << i.getScore() << "\tвозраст:\t" << i.getAge() << std::endl;
        }
    }
    else
    {
        std::cout << "Студент(ка) не найден(а)!" << std::endl;
    }
    std::cout << "Всего элементов: " << result5.size() << std::endl;
    std::cout << std::endl;

    //-----------------------

    std::vector<Person> result6;

    copy_if(people.begin(), people.end(), std::back_inserter(result6), [](const Person& person) {
        return person.getAge() > 25 && person.getScore() > 140 && person.getName() == "Андрей";
    });

    if (result6.size() > 0)
    {
        for (auto &&i : result6)
        {
            std::cout << "Имя:\t" << i.getName() << "\tбаллы:\t" << i.getScore() << "\tвозраст:\t" << i.getAge() << std::endl;
        }
    }
    else
    {
        std::cout << "Студент(ка) не найден(а)!" << std::endl;
    }
    std::cout << "Всего элементов: " << result6.size() << std::endl;
    std::cout << std::endl;

    return 0;
}
