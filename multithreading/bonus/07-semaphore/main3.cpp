// C++20 — std::counting_semaphore и std::jthread.
#include <iostream>
#include <mutex>
#include <semaphore>
#include <thread>
#include <vector>

int main()
{
    std::counting_semaphore<2> slots(2);
    std::mutex mtx;
    int completed = 0;
    {
        std::vector<std::jthread> workers;
        workers.reserve(5);
        for (int id = 1; id <= 5; ++id)
            workers.emplace_back([&, id]() {
                slots.acquire();
                {
                    std::lock_guard<std::mutex> guard(mtx);
                    ++completed;
                    std::cout << "Finished job " << id << '\n';
                }
                slots.release();
            });
    } // Деструкторы jthread ждут; конечные функции не используют stop_token.
    std::cout << "Completed after automatic joins: " << completed << '\n';
    return completed == 5 ? 0 : 1;
}
