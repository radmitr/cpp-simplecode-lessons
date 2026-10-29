#include "ThreadPool.hpp"

#include <cstddef>
#include <future>
#include <iostream>

int main()
{
    // Один работник нужен для детерминированного примера отмены очереди.
    ThreadPool pool(1);
    std::promise<void> started;
    std::future<void> startedSignal = started.get_future();
    std::promise<void> release;
    std::shared_future<void> gate = release.get_future().share();

    std::future<int> running = pool.submit([&started, gate]() {
        started.set_value();
        gate.wait(); // Уже выполняющаяся задача остаётся занята до сигнала.
        return 42;
    });
    startedSignal.wait();

    std::future<int> pending1 = pool.submit([]() { return 1; });
    std::future<int> pending2 = pool.submit([]() { return 2; });
    const std::size_t cancelled = pool.cancelPending();
    std::cout << "Cancelled queued tasks: " << cancelled << '\n';
    release.set_value(); // Работающую задачу cancelPending не прерывает.

    const int value = running.get();
    std::cout << "Running task result: " << value << '\n';
    int errors = 0;
    std::future<int>* pending[] = {&pending1, &pending2};
    for (std::future<int>* result : pending)
    {
        try
        {
            result->get();
        }
        catch (const std::future_error& error)
        {
            if (error.code() == std::make_error_code(std::future_errc::broken_promise))
            {
                ++errors;
                std::cout << "Queued task cancelled: broken_promise\n";
            }
            else
            {
                throw;
            }
        }
    }

    // Пул остаётся открытым для новых заданий.
    const int next = pool.submit([]() { return 7; }).get();
    std::cout << "Next task result: " << next << '\n';
    return cancelled == 2 && errors == 2 && value == 42 && next == 7 ? 0 : 1;
}
