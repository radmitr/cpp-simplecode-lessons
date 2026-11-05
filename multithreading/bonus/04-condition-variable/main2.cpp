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

    {
        std::unique_lock<std::mutex> lock(mtx);
        // Производителя ещё нет, поэтому ready останется false.
        // Главный поток ждёт до истечения таймаута 100 мс;
        // wait_for вернёт false.
        const bool received = cv.wait_for(
            lock, std::chrono::milliseconds(100), [&]() { return ready; });
        // После возврата wait_for мьютекс mtx снова захвачен.
        std::cout << "wait_for: " << (received ? "ready" : "timeout") << '\n';
    } // При выходе из блока деструктор lock освобождает mtx.

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
        // После возврата wait_until мьютекс mtx захвачен даже при таймауте.
        std::cout << "wait_until: " << (received ? "ready" : "timeout") << '\n';
    } // Деструктор lock освобождает mtx до join().
    // При таймауте производителю ещё может понадобиться mtx для ready = true.
    // Поэтому дожидаемся его завершения после освобождения mtx.
    producer.join();
}
