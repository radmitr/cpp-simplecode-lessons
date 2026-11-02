// C++11 — std::future, std::async и политики std::launch.
#include <future>
#include <iostream>
#include <stdexcept>

int main()
{
    auto result = std::async(std::launch::async, []() { return 2 + 5; });
    result.wait(); // Ждём готовности, но пока не забираем значение.
    result.wait(); // Допустимо: первый wait() не израсходовал результат.
    std::cout << "Valid before get: " << std::boolalpha << result.valid() << '\n';

    const int value = result.get();
    std::cout << "Result: " << value << '\n';
    std::cout << "Valid after get: " << result.valid() << '\n';
    // result.get() и result.wait() здесь уже недопустимы.
    // Само полученное число value можно использовать многократно.

    auto failed = std::async(std::launch::async, []() -> int {
        throw std::runtime_error("Saved error");
    });
    failed.wait(); // Ждёт готовности исключения, но не выбрасывает его.
    std::cout << "wait returned without throwing\n";
    bool caught = false;
    try
    {
        failed.get(); // Именно get() извлекает сохранённое исключение.
    }
    catch (const std::runtime_error& error)
    {
        std::cout << "Caught: " << error.what() << '\n';
        caught = true;
    }
    return value == 7 && !result.valid() && caught ? 0 : 1;
}
