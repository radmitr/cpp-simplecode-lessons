#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <stdexcept>
#include <thread>
#include <vector>

using Sum = std::uint64_t;

Sum parallelSum(const std::vector<Sum>& values, std::size_t count)
{
    std::vector<Sum> partial(count, 0);
    std::vector<std::thread> workers;
    workers.reserve(count);
    for (std::size_t id = 0; id < count; ++id)
    {
        const std::size_t begin = values.size() * id / count;
        const std::size_t end = values.size() * (id + 1) / count;
        workers.emplace_back([&, id, begin, end]() {
            // Своя часть массива и свой элемент partial у каждого потока.
            partial[id] = std::accumulate(
                values.begin() + static_cast<std::ptrdiff_t>(begin),
                values.begin() + static_cast<std::ptrdiff_t>(end), Sum{0});
        });
    }
    for (std::thread& worker : workers)
        worker.join();
    return std::accumulate(partial.begin(), partial.end(), Sum{0});
}

int main()
{
    std::vector<Sum> values(4000000);
    for (std::size_t i = 0; i < values.size(); ++i)
        values[i] = i % 1000;

    constexpr Sum expected = 1998000000;
    auto measure = [&](const char* label, auto operation) {
        double totalMilliseconds = 0;
        Sum result = 0;
        for (int repetition = 0; repetition < 3; ++repetition)
        {
            const auto start = std::chrono::steady_clock::now();
            result = operation();
            const auto end = std::chrono::steady_clock::now();
            if (result != expected)
                throw std::runtime_error("Incorrect sum");
            totalMilliseconds += std::chrono::duration<double, std::milli>(end - start).count();
        }
        std::cout << label << ": sum = " << result << "; average ms = "
                  << std::fixed << std::setprecision(3) << totalMilliseconds / 3 << '\n';
    };

    std::cout << "Hardware concurrency hint: " << std::thread::hardware_concurrency() << '\n';
    measure("Sequential", [&]() {
        return std::accumulate(values.begin(), values.end(), Sum{0});
    });
    measure("2 threads", [&]() { return parallelSum(values, 2); });
    measure("4 threads", [&]() { return parallelSum(values, 4); });
    // Сравниваются суммы. Требования, чтобы потоки были быстрее, здесь нет.
}
