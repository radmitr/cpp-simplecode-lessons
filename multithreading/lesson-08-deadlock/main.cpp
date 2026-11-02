// C++11 — std::mutex и взаимная блокировка потоков.
#include <iostream>
#include <cstddef>
#include <mutex>
#include <thread>
#include "SimpleTimer.hpp"

#include "../../common/console.hpp"

std::mutex mtx1;
std::mutex mtx2;

void print()
{
    // mtx2.lock();
    // std::this_thread::sleep_for(std::chrono::milliseconds(1));
    // mtx1.lock();

    mtx1.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    mtx2.lock();

    for (std::size_t i = 0; i < 5; ++i)
    {
        for (std::size_t i = 0; i < 10; i++)
        {
            std::cout << '*';
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    // mtx1.unlock();
    // mtx2.unlock();

    mtx2.unlock();
    mtx1.unlock();
}

void print2()
{
    mtx1.lock();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    mtx2.lock();

    for (std::size_t i = 0; i < 5; ++i)
    {
        for (std::size_t i = 0; i < 10; i++)
        {
            std::cout << '#';
            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    mtx2.unlock();
    mtx1.unlock();
}

int main(void)
{
    console::setupConsoleEncoding();

    SimpleTimer timer;

    std::thread t1(print);
    std::thread t2(print2);

    t1.join();
    t2.join();

    return 0;
}
