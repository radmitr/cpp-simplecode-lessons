#include <chrono>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

int main()
{
    std::shared_mutex settingsMutex;
    std::mutex outputMutex;
    int setting = 0;

    auto read = [&](int id) {
        std::shared_lock<std::shared_mutex> lock(settingsMutex);
        const int snapshot = setting;
        {
            std::lock_guard<std::mutex> outputGuard(outputMutex);
            std::cout << "Reader " << id << " started; value: " << snapshot << '\n';
        }
        // Изображаем длительное чтение, всё ещё удерживая shared_lock.
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::lock_guard<std::mutex> outputGuard(outputMutex);
            std::cout << "Reader " << id << " finished; value: " << snapshot << '\n';
        }
    };

    std::thread reader1(read, 1);
    std::thread reader2(read, 2);
    std::thread reader3(read, 3);
    std::thread writer([&]() {
        // Для изменения нужен исключительный доступ.
        std::unique_lock<std::shared_mutex> lock(settingsMutex);
        setting = 42;
        std::lock_guard<std::mutex> outputGuard(outputMutex);
        std::cout << "Writer set value to " << setting << '\n';
    });

    reader1.join();
    reader2.join();
    reader3.join();
    writer.join();
    std::cout << "Final value: " << setting << '\n';
    return setting == 42 ? 0 : 1;
}
