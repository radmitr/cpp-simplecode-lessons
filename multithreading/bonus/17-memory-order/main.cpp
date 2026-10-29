#include <atomic>
#include <iostream>
#include <thread>

int main()
{
    std::atomic<int> counter{0};
    auto increment = [&]() {
        for (int i = 0; i < 100000; ++i)
        {
            // Нужна неделимость увеличения, но не публикация других данных.
            counter.fetch_add(1, std::memory_order_relaxed);
        }
    };
    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();

    const int result = counter.load(std::memory_order_relaxed);
    std::cout << "Relaxed counter: " << result << '\n';
    return result == 200000 ? 0 : 1;
}
