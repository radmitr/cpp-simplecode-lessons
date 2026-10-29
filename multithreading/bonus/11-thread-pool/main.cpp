#include "ThreadPool.hpp"

#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <vector>

int main()
{
    std::vector<std::future<int>> results;
    std::future<int> failed;
    {
        ThreadPool pool(3); // Три постоянных потока для всех заданий.
        for (int value = 1; value <= 6; ++value)
        {
            results.push_back(pool.submit([value]() {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
                return value * value;
            }));
        }
        failed = pool.submit([]() -> int {
            throw std::runtime_error("Task failed");
        });
    } // Деструктор обработает оставшиеся задания и дождётся рабочих потоков.

    std::cout << "Pool destroyed: all queued tasks finished\n";
    int total = 0;
    for (std::future<int>& result : results)
    {
        const int value = result.get();
        total += value;
        std::cout << "Result: " << value << '\n';
    }

    bool exceptionReceived = false;
    try
    {
        failed.get();
    }
    catch (const std::exception& error)
    {
        exceptionReceived = true;
        std::cout << "Caught: " << error.what() << '\n';
    }
    std::cout << "Sum of squares: " << total << '\n';
    return total == 91 && exceptionReceived ? 0 : 1;
}
