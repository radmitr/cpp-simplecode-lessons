#include <iostream>
#include <cstddef>
#include <mutex>
#include <thread>
#include "SimpleTimer.hpp"

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

std::mutex mtx;

void print(char ch)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    mtx.lock();

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

    mtx.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void setupConsoleEncoding()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif
}

int main(void)
{
    setupConsoleEncoding();

    SimpleTimer timer;

    // print('*');
    // print('#');
    // print('@');

    std::thread t1(print, '*');
    std::thread t2(print, '#');
    std::thread t3(print, '@');

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
