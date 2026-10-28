#include <iostream>

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
        //this->data = other.data; // this is done by default!

        this->size = other.size;
        this->data = new int[other.size];

        for (size_t i = 0; i < other.size; i++)
        {
            this->data[i] = other.data[i];
        }

        cout << "The Copy constructor called " << this << endl;
    }

    ~MyClass()
    {
        delete[] data;
        cout << "Destructor called " << this << endl;
    }

private:
    size_t size;
};

int main(void)
{
    setupConsoleEncoding();

    MyClass a(10);
    MyClass b(a);

    return 0;
}
