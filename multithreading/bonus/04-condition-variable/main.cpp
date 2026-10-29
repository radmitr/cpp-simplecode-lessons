#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

int main()
{
    std::mutex mtx;
    std::condition_variable cv;
    std::string message;
    bool ready = false;

    std::thread worker([&]() {
        std::unique_lock<std::mutex> lock(mtx);
        // wait отпускает mtx на время ожидания и захватывает перед возвратом.
        // Предикат проверяет состояние, в том числе после ложного пробуждения.
        cv.wait(lock, [&]() { return ready; });
        const std::string received = message;
        lock.unlock();

        std::cout << "Worker received: " << received << '\n';
    });

    std::cout << "Main: preparing data...\n";
    // Пауза изображает работу; правильность не зависит от её длительности.
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    {
        std::lock_guard<std::mutex> guard(mtx);
        message = "Hello from main";
        ready = true;
    }
    cv.notify_one();

    worker.join();
    std::cout << "Main: worker finished\n";
}
