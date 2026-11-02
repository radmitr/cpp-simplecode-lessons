// C++20 — std::latch::try_wait().
#include <iostream>
#include <latch>

int main()
{
    std::latch pending(2);
    const bool before = pending.try_wait(); // Счётчик точно больше нуля: false.
    pending.count_down();
    const bool halfway = pending.try_wait(); // По-прежнему false.
    pending.count_down();
    pending.wait(); // Достигнут ноль; вызов возвращает сразу.
    const bool after = pending.try_wait();
    // Даже при нуле стандарт допускает ложный false; это не провал проверки.
    std::cout << std::boolalpha << "Before: " << before << "; halfway: " << halfway
              << "; after zero: " << after << '\n';
    return !before && !halfway ? 0 : 1;
}
