// C++98 — основные типы, std::boolalpha и sizeof.
#include <iostream>

int main()
{
    int count = 3;
    double price = 2.5;
    char letter = 'A';
    bool ready = true;
    std::cout << count << ' ' << price << ' ' << letter << ' ' << std::boolalpha << ready << '\n';
    std::cout << "sizeof(char): " << sizeof(char) << '\n';
    std::cout << "OK moved-example-004\n";
}
