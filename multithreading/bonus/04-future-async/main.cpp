#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

int sum(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    return a + b;
}

int main()
{
    // launch::async явно выбирает выполнение в отдельном потоке.
    std::future<int> result = std::async(std::launch::async, sum, 2, 5);
    std::cout << "Main: can do other work while sum is running\n";

    // get() ждёт готовности и получает результат. Повторно вызывать get() нельзя.
    const int value = result.get();
    std::cout << "Result: " << value << '\n';

    std::future<int> failed = std::async(std::launch::async, []() -> int {
        throw std::runtime_error("Error from background task");
    });
    try
    {
        failed.get(); // Исключение из фоновой задачи будет выброшено здесь.
    }
    catch (const std::exception& error)
    {
        std::cout << "Caught: " << error.what() << '\n';
    }
    return value == 7 ? 0 : 1;
}
