// C++20 — std::barrier::arrive(), wait() и arrival_token.
#include <barrier>
#include <iostream>
#include <thread>
#include <utility>

int main()
{
    std::barrier sync(2);
    int independentWork = 0;
    std::thread first([&]() {
        auto ticket = sync.arrive(); // Счётчик уменьшен, но поток пока не ждёт.
        independentWork = 7; // Эта работа не требует данных второго потока.
        sync.wait(std::move(ticket)); // Только здесь ждём завершения этапа.
    });
    std::thread second([&]() { sync.arrive_and_wait(); });
    first.join();
    second.join();
    std::cout << "Independent work: " << independentWork << '\n';
    return independentWork == 7 ? 0 : 1;
}
