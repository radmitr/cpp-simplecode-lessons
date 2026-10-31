#include <iostream>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>

#if defined(__MINGW32__) && defined(__GLIBCXX__)
// В проверенной сборке MinGW/libstdc++ повторный call_once после исключения
// зависает внутри реализации pthread_once. Не запускаем этот путь на MinGW.
int main()
{
    std::cout << "Retry after exception is disabled for MinGW/libstdc++.\n"
              << "Run this example on Linux; main.cpp works on Windows.\n";
}
#else
int main()
{
    std::once_flag initFlag;
    int attempts = 0;
    std::string settings;
    std::mutex outputMtx;

    auto initialize = [&]() {
        ++attempts;
        if (attempts == 1)
        {
            throw std::runtime_error("Configuration unavailable");
        }
        settings = "server=localhost";
    };

    try
    {
        std::call_once(initFlag, initialize);
    }
    catch (const std::exception& error)
    {
        std::cout << "First attempt: " << error.what() << '\n';
    }

    // Исключение не отмечает initFlag как успешно выполненный.
    // Следующий вызов может снова запустить initialize.
    auto worker = [&](int id) {
        std::call_once(initFlag, initialize);
        std::lock_guard<std::mutex> guard(outputMtx);
        std::cout << "Worker " << id << ": " << settings << '\n';
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    t1.join();
    t2.join();

    std::cout << "Initialization attempts: " << attempts << '\n';
    return attempts == 2 && settings == "server=localhost" ? 0 : 1;
}
#endif
