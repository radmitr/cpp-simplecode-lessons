#include <algorithm>
#include <chrono>
#include <condition_variable>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

int main()
{
    constexpr std::size_t capacity = 2;
    std::queue<int> tasks;
    std::mutex mtx;
    std::condition_variable notEmpty;
    std::condition_variable notFull;
    bool closed = false;
    std::size_t peak = 0;
    int processed = 0;
    int total = 0;

    auto consume = [&](int id) {
        for (;;)
        {
            int task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                notEmpty.wait(lock, [&]() { return closed || !tasks.empty(); });
                if (tasks.empty())
                    return;
                task = tasks.front();
                tasks.pop();
            }
            notFull.notify_one(); // Освободилось место для производителя.
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
            {
                std::lock_guard<std::mutex> guard(mtx);
                ++processed;
                total += task;
                std::cout << "Consumer " << id << " processed " << task << '\n';
            }
        }
    };

    std::thread t1(consume, 1);
    std::thread t2(consume, 2);
    // Главный поток здесь является производителем.
    for (int task = 1; task <= 8; ++task)
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            notFull.wait(lock, [&]() { return tasks.size() < capacity; });
            tasks.push(task);
            peak = std::max(peak, tasks.size());
            std::cout << "Queued " << task << "; size: " << tasks.size() << '\n';
        }
        notEmpty.notify_one();
    }
    {
        std::lock_guard<std::mutex> guard(mtx);
        closed = true;
    }
    notEmpty.notify_all();
    t1.join();
    t2.join();

    std::cout << "Processed: " << processed << "; sum: " << total
              << "; peak queue: " << peak << '\n';
    return processed == 8 && total == 36 && peak <= capacity ? 0 : 1;
}
