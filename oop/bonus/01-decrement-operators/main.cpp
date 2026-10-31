#include <iostream>

struct Point
{
    int x;
    int y;

    Point& operator--()
    {
        --x;
        --y;
        return *this;
    }

    Point operator--(int)
    {
        Point previous = *this;
        --(*this);
        return previous;
    }
};

int main()
{
    Point a{5, 1};
    Point& reference = --a;
    std::cout << "Prefix: " << a.x << ", " << a.y << '\n';
    Point previous = a--;
    std::cout << "Postfix returned: " << previous.x << ", " << previous.y << '\n';
    std::cout << "Current: " << a.x << ", " << a.y << '\n';
    return &reference == &a && previous.x == 4 && previous.y == 0 &&
                   a.x == 3 && a.y == -1 ? 0 : 1;
}
