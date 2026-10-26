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
    setupConsoleEncoding();

    A a("Класс A наше сообщение");
    a.printMsg();

    B b;
    b.printMsg();

    return 0;
}
