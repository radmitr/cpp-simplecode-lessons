// C++20 — std::latch::arrive_and_wait().
#include <array>
#include <iostream>
#include <latch>
#include <thread>

int main()
{
    std::array<int, 3> values{};
    std::array<int, 3> totals{};
    std::latch prepared(3);
    auto work = [&](int id) {
        values[id] = (id + 1) * 10;
        prepared.arrive_and_wait(); // Сообщаем о готовности и ждём остальных.
        totals[id] = values[0] + values[1] + values[2];
    };
    std::thread first(work, 0), second(work, 1), third(work, 2);
    first.join();
    second.join();
    third.join();
    std::cout << "Totals: " << totals[0] << ' ' << totals[1] << ' ' << totals[2] << '\n';
    return totals == std::array<int, 3>{60, 60, 60} ? 0 : 1;
}
