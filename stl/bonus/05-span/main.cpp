// C++20 — std::span.
#include <array>
#include <iostream>
#include <span>

int main()
{
    std::array<int, 3> values{10, 20, 30};
    std::span<int, 3> all(values); // Статическая длина 3 записана в типе.
    std::span<int> tail = all.subspan(1); // Динамическая длина: 2.
    tail[0] = 99; // Изменяем тот же values[1], отдельного массива нет.
    std::span<const int> readOnly = all;
    std::cout << "Original: " << values[0] << ' ' << values[1] << ' ' << values[2] << '\n';
    std::cout << "Tail size: " << tail.size() << "; read only: " << readOnly[1] << '\n';
    return values[1] == 99 && tail.size() == 2 && tail.data() == values.data() + 1 ? 0 : 1;
}
