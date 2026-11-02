// C++20 — std::barrier::arrive_and_drop().
#include <array>
#include <barrier>
#include <iostream>
#include <thread>

int main()
{
    int phases = 0;
    std::array<int, 3> visits{};
    std::barrier sync(3, [&]() noexcept { ++phases; });
    auto regular = [&](int id) {
        for (int phase = 0; phase < 3; ++phase)
        {
            ++visits[id];
            sync.arrive_and_wait();
        }
    };
    std::thread first(regular, 0), second(regular, 1);
    std::thread leaving([&]() {
        ++visits[2];
        sync.arrive_and_drop(); // Отмечает прибытие, не ждёт; больше не участвуем.
    });
    first.join();
    second.join();
    leaving.join();
    std::cout << "Phases: " << phases << "; visits: "
              << visits[0] << ' ' << visits[1] << ' ' << visits[2] << '\n';
    return phases == 3 && visits == std::array<int, 3>{3, 3, 1} ? 0 : 1;
}
