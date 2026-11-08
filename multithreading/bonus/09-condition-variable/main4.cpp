// C++11 — std::condition_variable и std::unique_lock.
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

int main()
{
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;
    int value = 0;
    std::unique_lock<std::mutex> lock(mtx);
    const auto first = cv.wait_for(lock, std::chrono::milliseconds(0));
    const auto second = cv.wait_until(lock, std::chrono::steady_clock::now());
    std::cout << "wait_for: " << (first == std::cv_status::timeout ? "timeout" : "no_timeout") << '\n';
    std::cout << "wait_until: " << (second == std::cv_status::timeout ? "timeout" : "no_timeout") << '\n';
    std::thread producer([&]() {
        {
            std::lock_guard<std::mutex> guard(mtx);
            value = 42;
            ready = true;
        }
        cv.notify_one();
    });
    while (!ready)
        cv.wait(lock); // После любого пробуждения снова проверяем ready под mtx.
    const int received = value;
    lock.unlock(); // Производитель должен иметь возможность завершиться до join.
    producer.join();
    std::cout << "Received: " << received << '\n';
    return received == 42 ? 0 : 1;
}
