// C++98 — sizeof массива, strlen() и завершающий ноль.
#include <cstring>
#include <iostream>

int main()
{
    char text[] = "Hello";
    std::cout << text << '\n';
    std::cout << "Length: " << std::strlen(text) << "; bytes: " << sizeof(text) << '\n';
    text[0] = 'h';
    std::cout << text << '\n';
    std::cout << "OK moved-example-060\n";
}
