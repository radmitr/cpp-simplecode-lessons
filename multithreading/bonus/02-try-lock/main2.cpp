#include <iostream>
#include <mutex>
#include <thread>

void tryIncrement(std::mutex& mtx, int& counter)
{
    // Конструктор вызывает mtx.try_lock(), не ожидая освобождения мьютекса.
    std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);
    if (lock.owns_lock())
    {
        ++counter;
        std::cout << "try_to_lock: acquired; counter = " << counter << '\n';
    }
    else
    {
        // Захват не удался: счётчик не меняем, unlock() не вызываем.
        std::cout << "try_to_lock: not acquired; skipping work\n";
    }
} // Деструктор lock освобождает mtx, только если захват был успешным.

int main()
{
    std::mutex mtx;
    int counter = 0;

    {
        std::lock_guard<std::mutex> owner(mtx);
        std::cout << "Main: holding the mutex\n";
        std::thread worker([&]() { tryIncrement(mtx, counter); });

        // worker пропустит увеличение, потому что mtx занят, и завершится.
        // try_to_lock не ждёт освобождения mtx, поэтому join() может закончиться.
        worker.join();
    } // owner освобождает mtx.

    std::cout << "Main: mutex released; trying again\n";
    tryIncrement(mtx, counter);
    // Как и try_lock(), эта попытка может не удаться даже при свободном mtx.
    std::cout << "Final counter: " << counter << '\n';
}
