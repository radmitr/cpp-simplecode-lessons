// C++98 — перегрузка оператора +.
#include <iostream>

#include "../../common/console.hpp"

using namespace std;

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

    Point operator+(const Point& other)
    {
        Point temp;

        temp.x = this->x + other.x;
        temp.y = this->y + other.y;

        return temp;
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
    console::setupConsoleEncoding();

    Point a(5, 1);
    Point b(9, 4);

    cout << "a: ";
    a.print();
    cout << "b: ";
    b.print();

    Point c = a + b; // d = a.operator+(b);
    cout << "c = a + b : ";
    c.print();

    return 0;
}
