// C++11 — std::promise и std::future.
#include <future>
#include <iostream>

int main()
{
    bool retrieved = false;
    bool satisfied = false;
    bool broken = false;
    std::promise<int> output;
    auto result = output.get_future();
    try
    {
        auto duplicate = output.get_future();
    }
    catch (const std::future_error& error)
    {
        retrieved = error.code() == std::make_error_code(std::future_errc::future_already_retrieved);
        std::cout << "Second get_future: future_already_retrieved\n";
    }
    output.set_value(7);
    try
    {
        output.set_value(8);
    }
    catch (const std::future_error& error)
    {
        satisfied = error.code() == std::make_error_code(std::future_errc::promise_already_satisfied);
        std::cout << "Second set_value: promise_already_satisfied\n";
    }

    std::future<int> abandoned;
    {
        std::promise<int> producer;
        abandoned = producer.get_future();
        // producer уничтожается, не предоставив ни значение, ни исключение.
    }
    try
    {
        abandoned.get();
    }
    catch (const std::future_error& error)
    {
        broken = error.code() == std::make_error_code(std::future_errc::broken_promise);
        std::cout << "Abandoned result: broken_promise\n";
    }
    const int value = result.get();
    std::cout << "Original result: " << value << '\n';
    // Невалидный future нельзя проверять повторным get(): используем valid().
    return retrieved && satisfied && broken && value == 7 && !result.valid() ? 0 : 1;
}
