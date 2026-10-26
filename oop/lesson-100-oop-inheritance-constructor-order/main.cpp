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
        cout << "Вызвался конструктор A" << endl;
    }
};

class B : private A
{
public:
    B()
    {
        cout << "Вызвался конструктор B" << endl;
    }
};

class C : private B
{
public:
    C()
    {
        cout << "Вызвался конструктор C" << endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    C c;

    return 0;
}
