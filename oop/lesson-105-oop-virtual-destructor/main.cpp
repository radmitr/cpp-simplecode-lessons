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
        cout << "выделена динамическая память, объект класса A" << endl;
    }

    virtual ~A()
    {
        cout << "освобождена динамическая память, объект класса A" << endl;
    }
};

class B : public A
{
public:
    B()
    {
        cout << "выделена динамическая память, объект класса B" << endl;
    }

    ~B() override
    {
        cout << "освобождена динамическая память, объект класса B" << endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    //B b;

    //B* bptr = new B();
    A* bptr = new B();
    delete bptr;

    return 0;
}
