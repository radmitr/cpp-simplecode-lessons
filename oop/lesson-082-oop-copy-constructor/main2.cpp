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
public:
    int data;

    MyClass(int data)
    {
        this->data = data;
        cout << "Constructor called " << this << endl;
    }

    ~MyClass()
    {
        cout << "Destructor called " << this << endl;
    }
};

void foo(MyClass value)
{
    cout << "Function FOO called" << endl;
}

MyClass foo2()
{
    cout << "Function FOO_2 called" << endl;
    MyClass temp(2);
    return temp;
}

int main(void)
{
    setupConsoleEncoding();

    // MyClass a(1);
    // foo(a);

    // только один вызов деструктора, потому что компилятор применил
    // оптимизацию возврата значения (RVO — Return Value Optimization)
    // чтобы отключить RVO - использовать флаг -fno-elide-constructors
    MyClass b = foo2();

    return 0;
}
