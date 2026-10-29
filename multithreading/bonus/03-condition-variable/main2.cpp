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

    {
        std::unique_lock<std::mutex> lock(mtx);
        // Производителя пока нет: условие останется false и наступит таймаут.
        const bool received = cv.wait_for(
            lock, std::chrono::milliseconds(100), [&]() { return ready; });
        std::cout << "wait_for: " << (received ? "ready" : "timeout") << '\n';
    }

    std::thread producer([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::lock_guard<std::mutex> guard(mtx);
            ready = true;
        }
        cv.notify_one();
    });

    {
        std::unique_lock<std::mutex> lock(mtx);
        // Один фиксированный момент времени вместо новой длительности ожидания.
        const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(2);
        const bool received = cv.wait_until(lock, deadline, [&]() { return ready; });
        std::cout << "wait_until: " << (received ? "ready" : "timeout") << '\n';
    }
    producer.join();
}
