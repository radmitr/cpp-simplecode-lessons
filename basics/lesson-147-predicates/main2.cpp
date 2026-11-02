// C++98 — предикаты и стандартные алгоритмы; C++11 — constexpr.
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "../../common/console.hpp"

using namespace std;

class Person
{
public:
    static constexpr double PASSING_SCORE = 180.0;

    Person(string name, double score)
    {
        this->Name = name;
        this->Score = score;
    }

    bool operator()(const Person& p) const
    {
        return p.Score > PASSING_SCORE;
    }

    string getName() const { return Name; }
    double getScore() const { return Score; }

private:
    string Name;
    double Score;
};

int main(void)
{
    console::setupConsoleEncoding();

    std::vector<Person> people = {
        Person("Вася", 181),
        Person("Петя", 30),
        Person("Маша", 179),
        Person("Даша", 200),
        Person("Катя", 198),
        Person("Андрей", 181),
        Person("Сергей", 50),
        Person("Иван", 150)
    };

    int result = std::count_if(people.begin(), people.end(), people.front());
    std::cout << result << std::endl;

    Person firstPerson = people.front();
    result = std::count_if(people.begin(), people.end(), firstPerson);
    std::cout << result << std::endl;

    return 0;
}
