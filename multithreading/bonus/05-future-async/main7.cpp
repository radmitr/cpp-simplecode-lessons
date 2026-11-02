// C++11 — std::future, std::async и политики std::launch.
#include <atomic>
#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int main()
{
    std::atomic<int> completed{0};
    const auto work = [&completed]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        return ++completed;
    };

    // (void) явно отбрасывает результат вызова, но не отменяет деструктор future.
    (void)std::async(std::launch::async, work);
    const int afterFirst = completed.load();
    (void)std::async(std::launch::async, work);
    const int afterSecond = completed.load();
    std::cout << "After first discarded future: " << afterFirst << '\n';
    std::cout << "After second discarded future: " << afterSecond << '\n';

    std::promise<void> release;
    auto gate = release.get_future().share();
    std::future<int> first;
    std::future<int> second;
    try
    {
        first = std::async(std::launch::async, [gate]() { gate.wait(); return 2; });
        second = std::async(std::launch::async, [gate]() { gate.wait(); return 5; });
    }
    catch (...)
    {
        // Если второй запуск не удался, не оставляем первый ждать навсегда.
        release.set_value();
        throw;
    }

    const auto firstStatus = first.wait_for(std::chrono::milliseconds(0));
    const auto secondStatus = second.wait_for(std::chrono::milliseconds(0));
    const bool bothWaiting = firstStatus == std::future_status::timeout &&
                             secondStatus == std::future_status::timeout;
    std::cout << "Both saved tasks still waiting: " << std::boolalpha
              << bothWaiting << '\n';
    release.set_value();
    const int total = first.get() + second.get();
    std::cout << "Saved results total: " << total << '\n';
    return afterFirst == 1 && afterSecond == 2 && bothWaiting && total == 7 ? 0 : 1;
}
