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
    int *data;

    MyClass(size_t size)
    {
        this->size = size;
        this->data = new int[size];

        for (size_t i = 0; i < size; i++)
        {
            data[i] = i;
        }

        cout << "Constructor called " << this << endl;
    }

    MyClass(const MyClass& other)
    {
        //this->data = other.data; // this is done by default (shallow copy)!

        this->size = other.size;
        this->data = new int[other.size];

        for (size_t i = 0; i < other.size; i++)
        {
            this->data[i] = other.data[i];
        }

        cout << "The Copy constructor called " << this << endl;
    }

    MyClass& operator=(const MyClass& other)
    {
        cout << "Operator = called " << this << endl;

        if (this->data != nullptr)
        {
            delete[] this->data;
        }

        this->size = other.size;
        this->data = new int[other.size];

        for (size_t i = 0; i < other.size; i++)
        {
            this->data[i] = other.data[i];
        }

        return *this;
    }

    ~MyClass()
    {
        delete[] data;
        cout << "Destructor called " << this << endl;
    }

private:
    size_t size;
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

    MyClass a(10);
    MyClass b(2);
    MyClass c(5);

    c = a = b;
    //a.operator=(b); // "a.operator=b;" equivalent to "a = b;"

    //MyClass c = a; // "MyClass c = a;" equivalent to "MyClass c(a);" - copy constructor

    return 0;
}
