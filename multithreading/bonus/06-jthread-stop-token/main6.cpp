// C++20 — std::stop_callback.
#include <future>
#include <iostream>
#include <stop_token>
#include <thread>

int main()
{
    std::promise<void> registered;
    auto ready = registered.get_future();
    std::promise<void> allowExit;
    auto exitGate = allowExit.get_future();
    const auto mainId = std::this_thread::get_id();
    bool callbackInMain = false;
    std::jthread worker([&](std::stop_token token) {
        std::stop_callback callback(token, [&]() {
            callbackInMain = std::this_thread::get_id() == mainId;
        });
        registered.set_value(); // callback уже зарегистрирован.
        exitGate.wait(); // Показывает: запрос сам по себе не завершает функцию.
    });
    ready.wait();
    worker.request_stop(); // Зарегистрированный callback выполняется здесь, в main.
    allowExit.set_value(); // Теперь разрешаем функции закончиться.
    worker.join();
    std::cout << std::boolalpha << "Callback executed in main: " << callbackInMain << '\n';
    return callbackInMain ? 0 : 1;
}
