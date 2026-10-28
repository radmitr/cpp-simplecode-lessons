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

class Test;

class Point
{
private:
    int x;
    int y;

public:
    Point()
    {
        this->x = 0;
        this->y = 0;
        cout << this << " constructor" << endl;
    }

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
        cout << this << " constructor" << endl;
    }

    bool operator==(const Point& other)
    {
        return this->x == other.x && this->y == other.y;
    }

    bool operator!=(const Point& other)
    {
        //return !operator==(other);
        return !(this->x == other.x && this->y == other.y);
    }

    Point operator+(const Point& other)
    {
        Point temp;

        temp.x = this->x + other.x;
        temp.y = this->y + other.y;

        return temp;
    }

    Point& operator++()
    {
        this->x++;
        this->y++;
        return *this;
    }

    Point operator++(int)
    {
        Point temp(*this);
        this->x++;
        this->y++;
        return temp;
    }

    int getX()
    {
        return this->x;
    }

    void setX(int x)
    {
        this->x = x;
    }

    int getY()
    {
        return this->y;
    }

    void setY(int y)
    {
        this->y = y;
    }

    void print()
    {
        cout << "x = " << this->x << ", y = " << this->y << endl;
    }

    friend void changeX(Point& value, Test& testValue);
};

class Test
{
public:
    int getData()
    {
        return data;
    }

private:
    int data = 0;
    friend void changeX(Point& value, Test& testValue);
};

void changeX(Point& value, Test& testValue)
{
    value.x = -1;
    testValue.data = -10;
}

int main(void)
{
    setupConsoleEncoding();

    Point a(5, 12);
    cout << "a: ";
    a.print();

    Test b;
    cout << "b: " << b.getData() << "\n" << endl;

    cout << "a: ";
    changeX(a, b);
    a.print();

    cout << "b: " << b.getData() << endl;

    return 0;
}
