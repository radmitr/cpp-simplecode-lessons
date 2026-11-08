// C++98 — int* const и const int*.
#include <iostream>

void increment(int* const value)
{
    ++*value; // Указатель не перенаправляется, но сам int изменяется.
}

void print(const int* value)
{
    std::cout << *value << '\n'; // Читать можно, менять через value нельзя.
}

int main()
{
    int value = 5;
    increment(&value);
    print(&value);
    std::cout << "OK moved-example-057\n";
}
