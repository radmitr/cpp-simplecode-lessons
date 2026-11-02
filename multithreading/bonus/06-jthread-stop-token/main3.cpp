// C++20 — std::jthread; request_stop() и join() при уничтожении.
#include <future>
#include <iostream>
#include <stop_token>
#include <thread>

int main()
{
    bool noticedStop = false;
    std::promise<void> started;
    auto ready = started.get_future();
    {
        std::jthread worker([&](std::stop_token stop) {
            started.set_value();
            while (!stop.stop_requested())
                std::this_thread::yield(); // Короткая демонстрация; для работы см. бонус 23.
            noticedStop = true;
        });
        ready.wait(); // Поток действительно начал функцию; длительность сна не угадываем.
    } // Деструктор: запросить остановку, дождаться выхода из функции.
    std::cout << std::boolalpha << "Stop noticed: " << noticedStop << '\n';
    return noticedStop ? 0 : 1;
}
