// C++11 — std::future, std::async и политики std::launch; C++14 — захват лямбды с инициализацией.
#include <chrono>
#include <future>
#include <iostream>
#include <utility>

int main()
{
    std::promise<void> release;
    auto gate = release.get_future();
    auto result = std::async(std::launch::async, [gate = std::move(gate)]() {
        gate.wait();
        return 7;
    });

    // wait_until получает момент времени, wait_for — длительность.
    const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(20);
    const auto first = result.wait_until(deadline);
    std::cout << "Before release: "
              << (first == std::future_status::timeout ? "timeout" : "unexpected") << '\n';
    release.set_value();
    result.wait();
    // Уже готовый результат доступен и после истечения прежнего deadline.
    const auto second = result.wait_until(deadline);
    std::cout << "Already ready: "
              << (second == std::future_status::ready ? "ready" : "unexpected") << '\n';
    const int value = result.get();
    std::cout << "Result: " << value << '\n';
    return first == std::future_status::timeout &&
                   second == std::future_status::ready && value == 7 ? 0 : 1;
}
