// C++11 — запуск лямбда-выражения в std::thread.
#include <chrono>
#include <cstddef>
#include <iostream>
#include <thread>

#include "../../common/console.hpp"

int sum(int a, int b)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tsum STARTED\t============" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tsum STOPPED\t============" << std::endl;
    return a + b;
}

int main(void)
{
    console::setupConsoleEncoding();

    // int result = sum(2, 5);
    // std::cout << "Result: " << result << std::endl;

    // std::thread t(sum, 2, 5);

    // int result;
    // auto f = [&result]() { result = sum(2, 5); };
    // std::thread t(f);

    int result;
    std::thread t([&result]() { result = sum(2, 5); });

    for (std::size_t i = 0; i < 10; i++)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << "\tmain\t" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    t.join();

    std::cout << "sum result: " << result << std::endl;

    return 0;
}
