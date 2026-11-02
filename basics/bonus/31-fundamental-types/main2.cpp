// C++98 — размер массива через sizeof.
#include <cstddef>
#include <iostream>

int main()
{
    int values[5] = {1, 2, 3, 4, 5};
    const std::size_t count = sizeof(values) / sizeof(values[0]);
    std::cout << "sizeof(int): " << sizeof(int) << '\n';
    std::cout << "elements: " << count << '\n';
    std::cout << "OK moved-example-028\n";
}
