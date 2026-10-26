#include <iostream>
#include <cstdlib>
#include <clocale>
#include <string>

using namespace std;

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
