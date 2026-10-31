#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <stop_token>
#include <thread>

int main()
{
    std::mutex mtx;
    std::condition_variable_any cv;
    bool ready = false;
    int message = 0;
    int received = 0;
    std::promise<void> started;
    std::future<void> startSignal = started.get_future();

    std::jthread worker([&](std::stop_token stop) {
        std::unique_lock<std::mutex> lock(mtx);
        started.set_value();
        const bool hasData = cv.wait(lock, stop, [&]() { return ready; });
        if (hasData)
        {
            received = message; // wait() вернулся с захваченным mtx.
        }
        lock.unlock();
        std::cout << "Wait result: " << std::boolalpha << hasData << '\n';
        std::cout << "Worker received: " << received << '\n';
    });

    startSignal.wait();
    {
        std::lock_guard<std::mutex> guard(mtx);
        message = 42;
        ready = true;
    }
    cv.notify_one();
    worker.join(); // Здесь остановка не запрашивается: пришли данные.
    return received == 42 ? 0 : 1;
}
