#include <iostream>

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
private:

public:
    MyClass();
    ~MyClass();

    void printMessages();
};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

void MyClass::printMessages()
{
    cout << "Hello!" << endl;
}

int main(void)
{
    setupConsoleEncoding();

    MyClass a;
    a.printMessages();

    return 0;
}
