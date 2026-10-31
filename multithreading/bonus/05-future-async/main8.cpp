#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <thread>

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout << "Use --uncaught or --unjoined. Expected exit code: 86.\n";
        return 0;
    }
    if (argc != 2 || (std::string_view(argv[1]) != "--uncaught" &&
                      std::string_view(argv[1]) != "--unjoined"))
    {
        std::cerr << "Unknown mode\n";
        return 2;
    }

    // По умолчанию terminate вызывает abort. Для урока задаём наблюдаемый
    // обработчик и известный код завершения. Он никогда не возвращает управление.
    std::set_terminate([]() {
        std::fputs("std::terminate called; exiting with 86\n", stderr);
        std::fflush(stderr);
        std::_Exit(86);
    });

    if (std::string_view(argv[1]) == "--uncaught")
    {
        std::thread worker([]() {
            throw std::runtime_error("Exception escaped the worker");
        });
        worker.join(); // Исключение не переносится сюда: terminate вызовет рабочий поток.
    }
    else
    {
        std::thread worker([]() {});
        // Даже если функция уже завершилась, worker остаётся joinable.
        // Уничтожение такого объекта без join()/detach() вызывает terminate.
    }
    return 1; // В обоих демонстрационных режимах эта строка недостижима.
}
