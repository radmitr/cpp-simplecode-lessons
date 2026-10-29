#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

int main()
{
    std::mutex mtx;
    std::condition_variable cv;
    bool ready = false;

    auto worker = [&](int id) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return ready; });
        // lock остаётся захвачен: сообщения печатаются по одному.
        std::cout << "Worker " << id << ": ready\n";
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    {
        std::lock_guard<std::mutex> guard(mtx);
        ready = true;
    }
    cv.notify_all(); // Пробуждает всех, кто уже ожидает.

    // Если поток начнёт ждать позже, предикат сразу увидит ready == true.
    t1.join();
    t2.join();
    t3.join();
}
