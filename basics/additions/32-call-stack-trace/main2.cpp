// C++98 — рекурсия и действия после вложенного вызова.
#include <iostream>

void countdown(int value)
{
    if (value == 0)
        return; // Базовый случай останавливает вложенные вызовы.
    std::cout << "Before: " << value << '\n';
    countdown(value - 1);
    std::cout << "After: " << value << '\n';
}

int main()
{
    countdown(3);
    std::cout << "OK moved-example-043\n";
}
