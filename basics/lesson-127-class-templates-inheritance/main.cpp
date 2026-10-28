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
//#include <typeinfo>

using namespace std;

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

template<class T>
class TypeSize
{
public:
    TypeSize(T value)
    {
        this->value = value;
    }

    void showDataTypeSize()
    {
        cout << sizeof(T) << endl;
    }

    T getValue()
    {
        return value;
    }

protected:
    T value;
};

template<class T>
class TypeInfo : public TypeSize<T>
{
public:
    TypeInfo(T value) : TypeSize<T>(value)
    {
    }

    void showTypeName()
    {
        cout << "Название типа: " << typeid(this->value).name() << endl;
    }

private:
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

    double a = 5;
    TypeInfo<double> ti(a);
    ti.showDataTypeSize();
    ti.showTypeName();

    int b = 10;
    TypeInfo<int> ti2(b);
    ti2.showDataTypeSize();
    ti2.showTypeName();

    Point p;
    TypeInfo<Point> ti3(p);
    ti3.showDataTypeSize();
    ti3.showTypeName();

    return 0;
}
