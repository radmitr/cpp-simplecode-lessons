// C++98 — функциональный макрос и приоритет операций.
#include <iostream>

#define MULTIPLY(x, y) ((x) * (y))

int main()
{
    std::cout << MULTIPLY(2 + 3, 4 + 1) << '\n';
    std::cout << "OK moved-example-067\n";
}
