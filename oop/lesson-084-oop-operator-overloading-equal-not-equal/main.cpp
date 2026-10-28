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

class Point
{
private:
    int x;
    int y;

public:
    Point()
    {
        x = 0;
        y = 0;
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

    int getX()
    {
        return x;
    }

    void setX(int x)
    {
        this->x = x;
    }

    int getY()
    {
        return y;
    }

    void setY(int y)
    {
        this->y = y;
    }

    void print()
    {
        cout << "x = " << x << ", y = " << y << endl;
    }
};

int main(void)
{
    setupConsoleEncoding();

    Point a(5, 1);
    Point b(9, 4);
    Point c(9, 4);

    cout << "a: ";
    a.print();
    cout << "b: ";
    b.print();
    cout << "c: ";
    c.print();

    bool result = a == b;
    cout << "a == b : " << result << endl;

    bool result2 = a != b;
    cout << "a != b : " << result2 << endl;

    bool result3 = b == c;
    cout << "b == c : " << result3 << endl;

    bool result4 = b != c;
    cout << "b != c : " << result4 << endl;

    return 0;
}
