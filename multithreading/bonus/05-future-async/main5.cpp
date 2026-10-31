#include <chrono>
#include <future>
#include <iostream>
#include <thread>

int main()
{
    const auto mainId = std::this_thread::get_id();
    int calls = 0;
    auto result = std::async(std::launch::deferred, [&]() {
        ++calls;
        return std::this_thread::get_id();
    });

    const auto status = result.wait_for(std::chrono::milliseconds(0));
    std::cout << "Timed wait: "
              << (status == std::future_status::deferred ? "deferred" : "unexpected") << '\n';
    std::cout << "Calls before get: " << calls << '\n';
    const auto executionId = result.get(); // Здесь начинается выполнение функции.
    std::cout << "Executed in main: " << std::boolalpha << (executionId == mainId) << '\n';

    auto byWait = std::async(std::launch::deferred, [&calls]() { return ++calls; });
    byWait.wait(); // Обычный wait() тоже запускает deferred-функцию.
    const int second = byWait.get(); // Повторного выполнения функции нет.
    {
        auto unused = std::async(std::launch::deferred, [&calls]() { return ++calls; });
        // Уничтожение без get()/wait() не запускает отложенную функцию.
    }
    std::cout << "Calls after get, wait and discarded deferred: " << calls << '\n';
    return status == std::future_status::deferred &&
                   executionId == mainId && second == 2 && calls == 2 ? 0 : 1;
}
