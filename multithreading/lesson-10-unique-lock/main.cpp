// C++11 — std::unique_lock, std::defer_lock и явные lock() / unlock().
#include <chrono>
#include <cstddef>
#include <iostream>
#include <mutex>
#include <thread>

#include "../../common/console.hpp"
#include "SimpleTimer.hpp"

std::mutex mtx;

// void print(char ch)
// {
//     // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//     // std::unique_lock<std::mutex> lock(mtx);

//     std::unique_lock<std::mutex> lock(mtx, std::defer_lock);

//     std::this_thread::sleep_for(std::chrono::milliseconds(2000));

//     lock.lock();

//     for (std::size_t i = 0; i < 5; ++i)
//     {
//         for (std::size_t i = 0; i < 10; i++)
//         {
//             std::cout << ch;
//             std::this_thread::sleep_for(std::chrono::milliseconds(10));
//         }
//         std::cout << std::endl;
//     }
//     std::cout << std::endl;

//     lock.unlock();

//     std::this_thread::sleep_for(std::chrono::milliseconds(2000));
// }

void print(char ch)
{
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock);

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    lock.lock();

    for (std::size_t i = 0; i < 5; ++i)
    {
        for (std::size_t i = 0; i < 10; i++)
        {
            std::cout << ch;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    SimpleTimer timer;

    std::thread t1(print, '*');
    std::thread t2(print, '#');

    t1.join();
    t2.join();

    return 0;
}
