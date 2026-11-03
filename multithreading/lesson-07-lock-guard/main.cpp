// C++11 — std::lock_guard и автоматическое освобождение мьютекса.
#include <chrono>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <thread>

#include "../../common/console.hpp"
#include "SimpleTimer.hpp"

std::mutex mtx;

void print(char ch)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    {
        std::lock_guard<std::mutex> guard(mtx);
        for (std::size_t i = 0; i < 5; ++i)
        {
            for (std::size_t i = 0; i < 10; i++)
            {
                std::cout << ch;
                std::this_thread::sleep_for(std::chrono::milliseconds(20));
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

int main(void)
{
    console::setupConsoleEncoding();

    SimpleTimer timer;

    std::thread t1(print, '*');
    std::thread t2(print, '#');
    std::thread t3(print, '@');

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
