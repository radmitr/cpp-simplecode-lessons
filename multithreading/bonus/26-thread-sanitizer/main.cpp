#include <iostream>
#include <mutex>
#include <thread>

int main()
{
    constexpr int iterations = 100000;
    int counter = 0;
    std::mutex mtx;
    auto increment = [&]() {
        for (int i = 0; i < iterations; ++i)
        {
            std::lock_guard<std::mutex> guard(mtx);
            ++counter; // Все обращения во время работы защищены одним mutex.
        }
    };

    std::thread t1(increment);
    std::thread t2(increment);
    t1.join();
    t2.join();

    // Потоки завершились: чтение результата больше не требует mutex.
    std::cout << "Expected: " << iterations * 2 << "\nObserved: " << counter << '\n';
    return counter == iterations * 2 ? 0 : 1;
}
