#include <array>
#include <cstddef>
#include <iostream>
#include <latch>
#include <numeric>
#include <thread>
#include <vector>

int main()
{
    std::array<int, 3> results{};
    std::latch finished(3);
    std::vector<std::thread> workers;
    workers.reserve(results.size());

    for (std::size_t i = 0; i < results.size(); ++i)
    {
        workers.emplace_back([&, i]() {
            // Изображаем подготовку трёх независимых наборов данных.
            // Каждый поток записывает только в свой элемент массива.
            results[i] = static_cast<int>((i + 1) * 10);
            finished.count_down();
            // count_down() сообщает о результате, но не завершает поток.
        });
    }

    finished.wait(); // Ждём, пока счётчик уменьшится с 3 до 0.
    // Записи перед count_down() уже видны после успешного ожидания.
    const int total = std::accumulate(results.begin(), results.end(), 0);
    std::cout << "Prepared values:";
    for (int value : results)
    {
        std::cout << ' ' << value;
    }
    std::cout << "\nTotal: " << total << '\n';

    // latch ждёт события, а join() — полного завершения каждого потока.
    for (auto& worker : workers)
    {
        worker.join();
    }
    return total == 60 ? 0 : 1;
}
