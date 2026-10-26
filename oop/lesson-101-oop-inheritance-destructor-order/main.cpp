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
        cout << "Вызвался конструктор класса A" << endl;
    }

    ~A()
    {
        cout << "Вызвался деструктор класса A" << endl;;
    }
};

class B : private A
{
public:
    B()
    {
        cout << "Вызвался конструктор класса B" << endl;
    }

    ~B()
    {
        cout << "Вызвался деструктор класса B" << endl;;
    }
};

class C : private B
{
public:
    C()
    {
        cout << "Вызвался конструктор класса C" << endl;
    }

    ~C()
    {
        cout << "Вызвался деструктор класса C" << endl;;
    }
};

int main(void)
{
    setupConsoleEncoding();

    C c;
    cout << endl;

    return 0;
}
