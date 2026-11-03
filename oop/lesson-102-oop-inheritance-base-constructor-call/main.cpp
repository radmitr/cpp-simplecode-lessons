// C++98 — вызов конструктора базового класса.
#include <cstdlib>
#include <iostream>
#include <string>

#include "../../common/console.hpp"

using namespace std;

class A
{
public:
    A()
    {
        msg = "Пустое сообщение";
    }

    A(string str)
    {
        msg = str;
    }

    A(string str, int a)
    {
        msg = str;
        value = a;
    }

    void printMsg()
    {
        cout << msg << endl;
    }

private:
    string msg;
    int value;
};

class B : public A
{
public:
    B() : A("Конструктор класса A", 100)
    {
    }
};

int main(void)
{
    console::setupConsoleEncoding();

    A a("Класс A наше сообщение");
    a.printMsg();

    B b;
    b.printMsg();

    return 0;
}
