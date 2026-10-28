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

template<typename T1, typename T2>
class MyClass
{
public:
    MyClass(T1 value, T2 value2)
    {
        this->value = value;
        this->value2 = value2;
    }

    void dataTypeSize()
    {
        cout << "value: " << sizeof(T1) << endl;
        cout << "value2: " << sizeof(T2) << endl;
    }

    T1 getValue()
    {
        return value;
    }

    T2 getValue2()
    {
        return value2;
    }

private:
    T1 value;
    T2 value2;
};

class Point
{
public:
    int x;
    int y;
    int z;

    Point() : x(0), y(0), z(0) {}

    Point(int x, int y, int z) : x(x), y(y), z(z) {}

    void print()
    {
        cout << "x=" << x << ", y=" << y << ", z=" << z << endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    int a = 5;
    Point point(11, 22, 33);
    MyClass<int, Point> myclass(a, point);
    myclass.dataTypeSize();

    int a1 = myclass.getValue();
    cout << a1 << endl;
    Point p = myclass.getValue2();
    p.print();

    return 0;
}
