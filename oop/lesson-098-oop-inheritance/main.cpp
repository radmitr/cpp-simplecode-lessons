// C++98 — наследование классов.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

class Human
{
public:
    string getName()
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

private:
    string name;
};

class Student : public Human
{
public:
    string group;

    void learn()
    {
        cout << "Я учусь!" << endl;
    }
};

class ExtramuralStudent : public Student
{
public:
    void learn()
    {
        cout << "Я бываю в университете реже обычного студента!" << endl;
    }
};

class Professor : public Human
{
public:
    string subject;
};

int main(void)
{
    console::setupConsoleEncoding();

    Human h;
    h.setName("Человеков человек человекович");
    cout << h.getName() << endl;

    Student st;
    st.setName("Студентов Иван Сидорович");
    cout << st.getName() << endl;
    st.learn();

    Professor pr;
    pr.setName("Профессоров Игорь Сергеевич");
    cout << pr.getName() << endl;

    ExtramuralStudent es;
    es.setName("Студентиков Михаил Сергеевич");
    cout << es.getName() << endl;
    es.learn();

    return 0;
}
