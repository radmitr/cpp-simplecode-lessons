// C++20 — std::jthread::joinable().
#include <future>
#include <iostream>
#include <thread>
#include <utility>

int main()
{
    std::jthread empty;
    std::promise<void> finished;
    auto ready = finished.get_future();
    std::jthread worker([&]() { finished.set_value(); });
    ready.wait();
    std::cout << std::boolalpha << "Empty: " << empty.joinable() << '\n';
    // Функция уже дошла до последней строки. Это само по себе не убирает связь.
    std::cout << "Before join: " << worker.joinable() << '\n';
    std::jthread owner = std::move(worker); // Теперь связь хранит owner.
    std::cout << "Moved from: " << worker.joinable() << '\n';
    owner.join(); // Разрешено и для уже завершившегося потока.
    std::cout << "After join: " << owner.joinable() << '\n';
    return empty.joinable() || worker.joinable() || owner.joinable() ? 1 : 0;
}
