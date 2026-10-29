#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

int main()
{
    std::timed_mutex mtx;
    int timeouts = 0;
    {
        std::lock_guard<std::timed_mutex> owner(mtx);
        std::thread worker([&]() {
            std::unique_lock<std::timed_mutex> lock(mtx, std::defer_lock);
            const bool first = lock.try_lock_for(std::chrono::milliseconds(50));
            std::cout << "try_lock_for while held: " << std::boolalpha << first << '\n';
            if (first)
                lock.unlock();
            else
                ++timeouts;

            const auto deadline = std::chrono::steady_clock::now()
                + std::chrono::milliseconds(50);
            const bool second = lock.try_lock_until(deadline);
            std::cout << "try_lock_until while held: " << second << '\n';
            if (second)
                lock.unlock();
            else
                ++timeouts;
        });
        // Рабочий поток вернётся по таймауту, хотя main всё ещё держит mtx.
        // С обычным lock() вместо ограниченного ожидания здесь был бы deadlock.
        worker.join();
    }

    std::unique_lock<std::timed_mutex> lock(mtx, std::defer_lock);
    const bool acquired = lock.try_lock_for(std::chrono::milliseconds(50));
    std::cout << "try_lock_for after release: " << acquired << '\n';
    // false допустим и для свободного мьютекса; unlock вручную не нужен.
    return timeouts == 2 ? 0 : 1;
}
