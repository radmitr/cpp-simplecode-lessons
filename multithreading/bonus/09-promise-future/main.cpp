#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <utility>

void calculate(std::promise<int> output, int a, int b)
{
    try
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        if (a < 0 || b < 0)
        {
            throw std::invalid_argument("Arguments must be non-negative");
        }
        output.set_value(a + b); // Делаем результат доступным через future.
    }
    catch (...)
    {
        output.set_exception(std::current_exception());
    }
}

bool runExample(int a, int b, bool expectError)
{
    std::promise<int> output;
    std::future<int> result = output.get_future();
    // promise нельзя копировать: передаём владение рабочему потоку.
    std::thread worker(calculate, std::move(output), a, b);
    std::cout << "Main: waiting for calculate(" << a << ", " << b << ")\n";

    bool correct = false;
    try
    {
        const int value = result.get();
        std::cout << "Result: " << value << '\n';
        correct = !expectError && value == a + b;
    }
    catch (const std::exception& error)
    {
        std::cout << "Caught: " << error.what() << '\n';
        correct = expectError;
    }
    worker.join(); // Готовность future не заменяет ожидание самого std::thread.
    return correct;
}

int main()
{
    const bool valueReceived = runExample(2, 5, false);
    const bool errorReceived = runExample(-2, 5, true);
    return valueReceived && errorReceived ? 0 : 1;
}
