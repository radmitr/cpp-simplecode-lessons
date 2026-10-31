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
    bool received = false;
    std::promise<void> started;
    std::future<void> startSignal = started.get_future();

    std::jthread worker([&](std::stop_token stop) {
        std::unique_lock<std::mutex> lock(mtx);
        started.set_value();

        // Ожидание закончится при ready == true или запросе остановки.
        // Результат сообщает значение предиката, а не причину пробуждения.
        received = cv.wait(lock, stop, [&]() { return ready; });
        lock.unlock();

        std::cout << "Wait result: " << std::boolalpha << received << '\n';
        std::cout << "Stop requested: " << stop.stop_requested() << '\n';
    });

    startSignal.wait();
    // Запрос не потеряется, даже если worker ещё не вошёл в wait().
    worker.request_stop();
    worker.join();

    std::cout << "Worker finished without data\n";
    return !received && !ready ? 0 : 1;
}
