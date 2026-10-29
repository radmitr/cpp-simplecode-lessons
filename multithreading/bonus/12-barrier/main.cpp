#include <array>
#include <barrier>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <numeric>
#include <thread>

int main()
{
    std::array<int, 3> partial{};
    std::barrier<> calculated(3);
    std::barrier<> printed(3);

    auto work = [&](std::size_t id) {
        for (int phase = 1; phase <= 3; ++phase)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(20 * (id + 1)));
            partial[id] = phase * static_cast<int>(id + 1);

            // Все результаты этапа должны быть записаны до их чтения.
            calculated.arrive_and_wait();
            if (id == 0)
            {
                const int total = std::accumulate(partial.begin(), partial.end(), 0);
                std::cout << "Phase " << phase << ": total = " << total << '\n';
            }

            // Не перезаписываем partial для нового этапа, пока идёт чтение.
            printed.arrive_and_wait();
        }
    };

    std::thread t1(work, 0);
    std::thread t2(work, 1);
    std::thread t3(work, 2);
    t1.join();
    t2.join();
    t3.join();

    const int total = std::accumulate(partial.begin(), partial.end(), 0);
    return total == 18 ? 0 : 1;
}
