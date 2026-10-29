#include <iostream>
#include <mutex>
#include <thread>

void tryIncrement(std::mutex& mtx, int& counter)
{
    if (mtx.try_lock())
    {
        // Мьютекс уже захвачен: с adopt_lock конструктор guard не вызывает lock() повторно.
        std::lock_guard<std::mutex> guard(mtx, std::adopt_lock);
        ++counter;
        std::cout << "try_lock: acquired; counter = " << counter << '\n';
    } // guard освобождает мьютекс только после успешного try_lock().
    else
    {
        // При неудаче нельзя обращаться к counter или вызывать mtx.unlock().
        std::cout << "try_lock: not acquired; skipping work\n";
    }
}

int main()
{
    std::mutex mtx;
    int counter = 0;

    {
        std::lock_guard<std::mutex> guard(mtx);
        std::cout << "Main: holding the mutex\n";
        std::thread worker([&]() { tryIncrement(mtx, counter); });

        // Здесь join безопасен: worker только пробует захват и не ждёт mtx.
        // Замена try_lock на lock привела бы к взаимному ожиданию.
        worker.join();
    } // Главный поток освобождает mtx.

    std::cout << "Main: mutex released; trying again\n";
    tryIncrement(mtx, counter);
    // Даже у свободного mutex стандарт допускает ложную неудачу try_lock().
    std::cout << "Final counter: " << counter << '\n';
}
