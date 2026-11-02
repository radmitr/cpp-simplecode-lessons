// C++11 — std::future, std::async и политики std::launch; C++14 — захват лямбды с инициализацией.
#include <chrono>
#include <future>
#include <iostream>
#include <utility>

int main()
{
    // Задача не сможет завершиться, пока main не подаст сигнал.
    std::promise<void> release;
    auto gate = release.get_future();
    auto result = std::async(std::launch::async, [gate = std::move(gate)]() {
        gate.wait();
        return 7;
    });

    const auto first = result.wait_for(std::chrono::milliseconds(20));
    std::cout << "Before release: "
              << (first == std::future_status::timeout ? "timeout" : "unexpected") << '\n';
    // Таймаут завершил только ожидание main; задача всё ещё существует.
    release.set_value();
    result.wait(); // Теперь действительно дожидаемся готовности.
    const auto second = result.wait_for(std::chrono::milliseconds(0));
    std::cout << "After completion: "
              << (second == std::future_status::ready ? "ready" : "unexpected") << '\n';
    const int value = result.get();
    std::cout << "Result: " << value << '\n';
    return first == std::future_status::timeout &&
                   second == std::future_status::ready && value == 7 ? 0 : 1;
}
