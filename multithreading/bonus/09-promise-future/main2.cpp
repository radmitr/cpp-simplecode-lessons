#include <atomic>
#include <future>
#include <iostream>
#include <thread>
#include <utility>

int main()
{
    std::promise<int> output;
    auto result = output.get_future();
    std::promise<void> resume;
    auto permission = resume.get_future();
    std::atomic<bool> finished{false};

    std::thread worker([output = std::move(output), permission = std::move(permission),
                        &finished]() mutable {
        output.set_value(7); // Результат готов, но функция ещё продолжает работу.
        permission.wait(); // Завершиться можно только после сигнала main.
        finished.store(true);
    });

    result.wait();
    result.wait(); // Эти вызовы не извлекают значение.
    const int value = result.get();
    const bool finishedAfterGet = finished.load();
    std::cout << "Result: " << value << '\n';
    std::cout << "Worker finished after get: " << std::boolalpha << finishedAfterGet << '\n';
    resume.set_value();
    worker.join();
    std::cout << "Worker finished after join: " << finished.load() << '\n';
    return value == 7 && !finishedAfterGet && finished.load() ? 0 : 1;
}
