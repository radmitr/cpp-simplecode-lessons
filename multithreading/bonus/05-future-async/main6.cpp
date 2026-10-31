#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int main()
{
    const auto mainId = std::this_thread::get_id();
    // Без явной политики реализация выбирает async или deferred.
    auto result = std::async([]() { return std::this_thread::get_id(); });
    const auto status = result.wait_for(std::chrono::milliseconds(0));
    const bool deferred = status == std::future_status::deferred;
    std::cout << "Selected: " << (deferred ? "deferred" : "async") << '\n';

    // get() работает в обоих случаях. При deferred он сам выполнит функцию.
    const auto executionId = result.get();
    const bool inMain = executionId == mainId;
    std::cout << "Executed in main: " << std::boolalpha << inMain << '\n';
    return deferred == inMain ? 0 : 1;
}
