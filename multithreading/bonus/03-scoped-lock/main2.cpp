#include <iostream>
#include <mutex>
#include <thread>

struct Account
{
    int balance = 10000;
    std::mutex mtx;
};

// Одна попытка перевода. При неудаче возвращаем false без удержания мьютексов.
bool tryTransfer(Account& from, Account& to)
{
    std::unique_lock<std::mutex> fromLock(from.mtx);
    std::cout << "First mutex acquired\n";

    std::cout << "Trying the second mutex\n";
    if (!to.mtx.try_lock())
    {
        std::cout << "Second mutex not acquired; releasing the first\n";
        fromLock.unlock();
        return false;
    }

    // try_lock() уже захватил второй мьютекс; guard будет освобождать его.
    std::lock_guard<std::mutex> toLock(to.mtx, std::adopt_lock);
    std::cout << "Both mutexes acquired; transferring one unit\n";
    --from.balance;
    ++to.balance;
    return true;
} // При успехе оба объекта lock освобождают свои мьютексы.

int main()
{
    Account first;
    Account second;
    bool transferred = false;

    {
        // Занимаем второй мьютекс, чтобы обязательно показать неудачную попытку.
        std::lock_guard<std::mutex> busy(second.mtx);
        std::cout << "Main: holding the second mutex\n";
        std::thread worker([&]() { transferred = tryTransfer(first, second); });
        // worker не ждёт второй мьютекс, поэтому он может завершиться.
        worker.join();
    } // main освобождает второй мьютекс.

    // После join() рабочий поток уже не обращается к transferred и счетам.
    std::cout << "Main: second mutex released; retrying\n";
    while (!transferred)
    {
        transferred = tryTransfer(first, second);
        // try_lock() может вернуть false даже для свободного мьютекса.
        if (!transferred)
        {
            // Даём другим потокам шанс поработать перед следующей попыткой.
            // Переключение на другой поток не гарантируется.
            std::this_thread::yield();
        }
    }

    std::cout << "First: " << first.balance << '\n';
    std::cout << "Second: " << second.balance << '\n';
    std::cout << "Total: " << first.balance + second.balance << '\n';
    return first.balance == 9999 && second.balance == 10001 ? 0 : 1;
}
