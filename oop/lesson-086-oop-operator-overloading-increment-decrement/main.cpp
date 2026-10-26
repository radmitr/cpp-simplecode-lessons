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
};

int main(void)
{
    setupConsoleEncoding();

    Point a(5, 1);
    cout << "a: ";
    a.print();
    cout << endl;

    Point b = ++a;
    cout << "a: ";
    a.print();
    cout << "b: ";
    b.print();
    cout << endl;

    b = a++;
    cout << "a: ";
    a.print();
    cout << "b: ";
    b.print();
    cout << endl;

    return 0;
}
