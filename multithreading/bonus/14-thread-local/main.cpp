#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

int incrementLocal()
{
    // Отдельная переменная для каждого потока; сохраняется между вызовами.
    thread_local int counter = 0;
    return ++counter;
}

int main()
{
    std::atomic<int> shared{0};
    std::mutex outputMutex;
    auto work = [&](int id) {
        int local = 0;
        for (int i = 0; i < 3; ++i)
        {
            local = incrementLocal();
            ++shared;
        }
        std::lock_guard<std::mutex> guard(outputMutex);
        std::cout << "Worker " << id << ": local = " << local << '\n';
    };

    std::thread t1(work, 1);
    std::thread t2(work, 2);
    t1.join();
    t2.join();

    // У главного потока своя counter: это его первый вызов.
    const int mainLocal = incrementLocal();
    std::cout << "Main: local = " << mainLocal << '\n';
    std::cout << "Shared total: " << shared.load() << '\n';
    return shared.load() == 6 && mainLocal == 1 ? 0 : 1;
}
