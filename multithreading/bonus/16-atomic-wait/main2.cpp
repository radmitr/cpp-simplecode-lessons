#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

int main()
{
    std::atomic<bool> ready{false};
    int payload = 0;
    int completed = 0;
    std::mutex outputMutex;

    auto read = [&](int id) {
        ready.wait(false);
        std::lock_guard<std::mutex> guard(outputMutex);
        ++completed;
        std::cout << "Reader " << id << " received: " << payload << '\n';
    };
    std::thread t1(read, 1);
    std::thread t2(read, 2);
    std::thread t3(read, 3);

    payload = 42;
    ready.store(true);
    ready.notify_all();
    t1.join();
    t2.join();
    t3.join();
    std::cout << "Completed readers: " << completed << '\n';
    return completed == 3 ? 0 : 1;
}
