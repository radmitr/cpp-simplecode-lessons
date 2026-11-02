// C++11 — std::unique_lock, std::defer_lock и явные lock() / unlock().
#include <iostream>
#include <cstddef>
#include <mutex>
#include <thread>
#include "SimpleTimer.hpp"

#include "../../common/console.hpp"

std::mutex mtx;

// void print(char ch)
// {
//     // std::this_thread::sleep_for(std::chrono::milliseconds(2000));
//     // std::unique_lock<std::mutex> ul(mtx);

//     std::unique_lock<std::mutex> ul(mtx, std::defer_lock);

//     std::this_thread::sleep_for(std::chrono::milliseconds(2000));

//     ul.lock();

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

//     ul.unlock();

//     std::this_thread::sleep_for(std::chrono::milliseconds(2000));
// }

void print(char ch)
{
    std::unique_lock<std::mutex> ul(mtx, std::defer_lock);

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    ul.lock();

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
