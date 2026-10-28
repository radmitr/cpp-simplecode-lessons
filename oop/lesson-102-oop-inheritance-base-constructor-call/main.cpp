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
