#include <iostream>
#include <cstdlib>
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

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

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
    setupConsoleEncoding();

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
