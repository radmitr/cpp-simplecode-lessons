// C++14 — std::shared_lock; C++17 — std::shared_mutex.
#include <future>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <thread>

int main()
{
    std::shared_mutex mtx;
    int value = 10;
    std::promise<void> gapOpened;
    auto gap = gapOpened.get_future();
    std::promise<void> changed;
    auto done = changed.get_future();
    std::thread writer([&]() {
        gap.wait();
        {
            std::unique_lock<std::shared_mutex> lock(mtx);
            value = 20;
        }
        changed.set_value();
    });

    std::shared_lock<std::shared_mutex> reader(mtx);
    const int snapshot = value;
    reader.unlock(); // Прямого атомарного upgrade у shared_mutex нет.
    gapOpened.set_value();
    done.wait(); // Гарантируем изменение именно в промежутке между захватами.
    bool updated = false;
    {
        std::unique_lock<std::shared_mutex> exclusive(mtx);
        if (value == snapshot) // Повторная проверка обязательна для нашего решения.
        {
            ++value;
            updated = true;
        }
    }
    writer.join();
    std::cout << "Snapshot: " << snapshot << "; final: " << value
              << "; updated from old snapshot: " << std::boolalpha << updated << '\n';
    return snapshot == 10 && value == 20 && !updated ? 0 : 1;
}
