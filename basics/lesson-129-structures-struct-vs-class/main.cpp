#include <iostream>
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

class MyClass
{
public:
    void print()
    {
        cout << a << endl;
    }

private:
    int a = 5;
};

struct MyStruct
{
public:
    MyStruct()
    {

    }

    MyStruct(int a)
    {
        this->a = a;
    }

    ~MyStruct()
    {

    }

    void print()
    {
        cout << a << endl;
    }

private:
    int a = 55;
};

int main(void)
{
    setupConsoleEncoding();

    MyClass mc;
    MyStruct ms;

    //cout << ms.a << endl;
    ms.print();

    return 0;
}
