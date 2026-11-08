// C++98 — потоковые операторы; C++11 — списковая инициализация.
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

#include "../../../basics/bonus/common/check.hpp"

struct Point { int x; int y; int z; };
std::istream& operator>>(std::istream& input, Point& point)
{
    Point candidate{};
    if (input >> candidate.x >> candidate.y >> candidate.z) point = candidate;
    return input;
}
std::ostream& operator<<(std::ostream& output, const Point& point)
{
    return output << point.x << ' ' << point.y << ' ' << point.z;
}

int main()
{
    try
    {
        Point value{9, 9, 9};
        std::istringstream valid("1 2 3");
        check(static_cast<bool>(valid >> value), "complete point");
        check(value.x == 1 && value.y == 2 && value.z == 3, "stored point");
        std::istringstream invalid("4 5 bad");
        check(!(invalid >> value), "third component fails");
        check(value.x == 1 && value.y == 2 && value.z == 3, "failed read preserves point");
        std::ostringstream output;
        output << value;
        check(output.str() == "1 2 3", "matching representation");
        std::cout << output.str() << "; invalid input left point unchanged\n";
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
