#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

int main()
{
    std::queue<int> tasks;
    std::mutex mtx;
    std::condition_variable cv;
    bool finished = false;
    int processed = 0;
    int total = 0;

    auto consume = [&](int id) {
        for (;;)
        {
            int task;
            {
                std::unique_lock<std::mutex> lock(mtx);
                cv.wait(lock, [&]() { return finished || !tasks.empty(); });
                if (tasks.empty())
                {
                    return; // Производитель закончил, очередь полностью обработана.
                }
                task = tasks.front();
                tasks.pop();
            }

            // Задание обрабатывается без удержания мьютекса очереди.
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            {
                std::lock_guard<std::mutex> guard(mtx);
                ++processed;
                total += task;
                std::cout << "Consumer " << id << " processed " << task << '\n';
            }
        }
    };

    std::thread consumer1(consume, 1);
    std::thread consumer2(consume, 2);
    std::thread producer([&]() {
        for (int task = 1; task <= 6; ++task)
        {
            {
                std::lock_guard<std::mutex> guard(mtx);
                tasks.push(task);
            }
            cv.notify_one();
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        {
            std::lock_guard<std::mutex> guard(mtx);
            finished = true;
        }
        cv.notify_all(); // Завершиться должны все потребители, включая спящих.
    });

    producer.join();
    consumer1.join();
    consumer2.join();
    std::cout << "Processed: " << processed << "; sum: " << total << '\n';
    return processed == 6 && total == 21 ? 0 : 1;
}
