// C++11 — thread_local и повторное использование потока в пуле.
#include <iostream>
#include "../11-thread-pool/ThreadPool.hpp"

int nextTaskNumber()
{
    thread_local int number = 0;
    return ++number;
}

int main()
{
    int first = 0, second = 0, nextPool = 0;
    {
        ThreadPool pool(1); // Один постоянный работник для обоих заданий.
        first = pool.submit(nextTaskNumber).get();
        second = pool.submit(nextTaskNumber).get();
    } // Работник завершается вместе с пулом, его thread_local больше не живёт.
    {
        ThreadPool pool(1); // Новый поток получает собственный новый number.
        nextPool = pool.submit(nextTaskNumber).get();
    }
    std::cout << "Same worker: " << first << ' ' << second
              << "; new pool: " << nextPool << '\n';
    return first == 1 && second == 2 && nextPool == 1 ? 0 : 1;
}
