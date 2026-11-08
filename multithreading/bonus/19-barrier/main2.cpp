// C++20 — std::barrier с функцией завершения этапа.
#include <array>
#include <barrier>
#include <iostream>
#include <numeric>
#include <thread>

int main()
{
    std::array<int, 3> partial{};
    std::array<int, 3> totals{};
    int finishedPhases = 0;
    auto complete = [&]() noexcept {
        // Все записи этапа закончены, следующий этап ещё не разрешён.
        totals[finishedPhases++] = std::accumulate(partial.begin(), partial.end(), 0);
    };
    std::barrier sync(3, complete);
    auto work = [&](int id) {
        for (int phase = 1; phase <= 3; ++phase)
        {
            partial[id] = phase * (id + 1);
            sync.arrive_and_wait();
        }
    };
    std::thread first(work, 0), second(work, 1), third(work, 2);
    first.join();
    second.join();
    third.join();
    for (int i = 0; i < finishedPhases; ++i)
        std::cout << "Phase " << i + 1 << ": total = " << totals[i] << '\n';
    return finishedPhases == 3 && totals == std::array<int, 3>{6, 12, 18} ? 0 : 1;
}
