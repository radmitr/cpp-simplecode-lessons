#include <iostream>
#include <memory>
#include <stdexcept>

struct DeleteWithMessage
{
    void operator()(int* value) const noexcept
    {
        std::cout << "release " << *value << '\n';
        delete value;
    }
};

enum class ExitMode { normal, earlyReturn, exception };

void process(ExitMode mode)
{
    // Владение сразу передаётся объекту: отдельного ручного delete в ветках нет.
    std::unique_ptr<int, DeleteWithMessage> resource(new int(42));
    std::cout << "acquire " << *resource << '\n';

    if (mode == ExitMode::earlyReturn)
    {
        std::cout << "early return\n";
        return;
    }
    if (mode == ExitMode::exception)
    {
        std::cout << "throw\n";
        throw std::runtime_error("operation failed");
    }
    std::cout << "normal exit\n";
}

int main()
{
    process(ExitMode::normal);
    process(ExitMode::earlyReturn);
    try
    {
        process(ExitMode::exception);
    }
    catch (const std::exception& error)
    {
        std::cout << "caught: " << error.what() << '\n';
    }
}
