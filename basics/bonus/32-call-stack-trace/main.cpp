// C++98 — вложенные вызовы функций.
#include <iostream>

void inner()
{
    int local = 7;
    std::cout << "inner: " << local << '\n';
}

void outer()
{
    std::cout << "outer entered\n";
    inner();
    std::cout << "outer resumed\n";
}

int main()
{
    outer();
    std::cout << "main resumed\n";
    std::cout << "OK moved-example-042\n";
}
