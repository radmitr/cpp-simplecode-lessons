#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

constexpr int iterations = 100000;

int countWithMutex()
{
    int counter = 0;
    std::mutex mtx;
    auto increment = [&]() {
        for (int i = 0; i < iterations; ++i)
        {
            std::lock_guard<std::mutex> guard(mtx);
            ++counter;
        }
    };

    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    return counter;
}

int countWithAtomic()
{
    std::atomic<int> counter{0};
    auto increment = [&]() {
        for (int i = 0; i < iterations; ++i)
        {
            ++counter; // Атомарное увеличение: чтение и запись как одна операция.
        }
    };

    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();
    return counter.load();
}

int main()
{
    const int expected = 2 * iterations;
    const int withMutex = countWithMutex();
    const int withAtomic = countWithAtomic();

    std::cout << "Expected: " << expected << '\n';
    std::cout << "Mutex:    " << withMutex << '\n';
    std::cout << "Atomic:   " << withAtomic << '\n';
    return withMutex == expected && withAtomic == expected ? 0 : 1;
}
