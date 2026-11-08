// C++14 — shared_timed_mutex и shared_lock; C++11 — async и promise.
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <mutex>
#include <shared_mutex>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::shared_timed_mutex mutex;
        int value = 0;
        std::promise<bool> attempted;
        auto attempt = attempted.get_future();
        std::future<int> reader; // При выходе живёт дольше writer и ждёт запущенную async-задачу.
        std::unique_lock<std::shared_timed_mutex> writer(mutex);
        reader = std::async(std::launch::async, [&] {
            bool signalled = false;
            try
            {
                std::shared_lock<std::shared_timed_mutex> lock(mutex, std::defer_lock);
                const bool by_duration = lock.try_lock_for(std::chrono::milliseconds(1));
                const bool by_deadline = lock.try_lock_until(std::chrono::steady_clock::now() + std::chrono::milliseconds(1));
                attempted.set_value(!by_duration && !by_deadline);
                signalled = true;
                lock.lock();
                return value;
            }
            catch (...)
            {
                if (!signalled) attempted.set_exception(std::current_exception());
                throw;
            }
        });
        const bool blocked = attempt.get();
        value = 42;
        writer.unlock();
        const int snapshot = reader.get();
        check(blocked && snapshot == 42, "reader waited for exclusive owner");
        std::cout << snapshot << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
