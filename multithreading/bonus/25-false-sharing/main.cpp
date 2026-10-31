#include <atomic>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <future>
#include <iomanip>
#include <iostream>
#include <new>
#include <thread>

namespace
{
#ifdef __cpp_lib_hardware_interference_size
constexpr std::size_t separation = std::hardware_destructive_interference_size;
#else
// Запасной учебный вариант для библиотек без этой константы.
// 64 байта — распространённое значение, но не гарантия для любого процессора.
constexpr std::size_t separation = 64;
#endif

struct alignas(separation) AdjacentCounters
{
    std::atomic<std::uint64_t> first{0};
    std::atomic<std::uint64_t> second{0};
};

struct alignas(separation) SeparateCounter
{
    std::atomic<std::uint64_t> value{0};
};

constexpr std::uint64_t iterations = 1000000;
constexpr int repetitions = 3;

bool measure(const char* name, std::atomic<std::uint64_t>& first,
             std::atomic<std::uint64_t>& second)
{
    double totalMilliseconds = 0;
    for (int run = 0; run < repetitions; ++run)
    {
        first.store(0, std::memory_order_relaxed);
        second.store(0, std::memory_order_relaxed);
        std::promise<void> start;
        std::shared_future<void> gate = start.get_future().share();
        auto increment = [gate](std::atomic<std::uint64_t>& counter) {
            gate.wait();
            for (std::uint64_t i = 0; i < iterations; ++i)
            {
                counter.fetch_add(1, std::memory_order_relaxed);
            }
        };

        const auto begin = std::chrono::steady_clock::now();
        std::thread t1([increment, &first]() { increment(first); });
        std::thread t2([increment, &second]() { increment(second); });
        start.set_value(); // Разрешаем обоим работникам приступить к счётчикам.
        t1.join();
        t2.join();
        const auto end = std::chrono::steady_clock::now();
        totalMilliseconds += std::chrono::duration<double, std::milli>(end - begin).count();

        if (first.load() != iterations || second.load() != iterations)
        {
            return false;
        }
    }

    std::cout << name << ": " << first.load() << ", " << second.load()
              << "; average " << totalMilliseconds / repetitions << " ms\n";
    return true;
}
}

int main()
{
    AdjacentCounters adjacent;
    SeparateCounter first;
    SeparateCounter second;

    std::cout << "Selected spacing: " << separation << " bytes\n";
    std::cout << "Adjacent counter offset: " << offsetof(AdjacentCounters, second)
              << " bytes\n";
    std::cout << std::fixed << std::setprecision(3);
    const bool adjacentOk = measure("Adjacent", adjacent.first, adjacent.second);
    const bool separateOk = measure("Separated", first.value, second.value);
    std::cout << "Timing depends on hardware and scheduling; no speedup is required.\n";
    return adjacentOk && separateOk ? 0 : 1;
}
