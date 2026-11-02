// C++20 — std::jthread и автоматический join().
#include <future>
#include <iostream>
#include <thread>

int main()
{
    int result = 0;
    std::promise<void> started;
    auto ready = started.get_future();
    {
        std::jthread worker([&]() {
            started.set_value();
            result = 42; // Конечная работа; запрос остановки здесь не проверяется.
        });
        ready.wait();
        // Деструктор запросит остановку, но функция просто завершит свою работу.
    } // Автоматический join позволяет безопасно читать result ниже.
    std::cout << "Result after automatic join: " << result << '\n';
    return result == 42 ? 0 : 1;
}
