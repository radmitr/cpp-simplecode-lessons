// C++11 — std::recursive_mutex.
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "../../common/console.hpp"

std::recursive_mutex rm;

void foo(int a)
{
    rm.lock();
    std::cout << a << " ";
    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    if (a <= 1)
    {
        std::cout << std::endl;
        rm.unlock();
        return;
    }
    a--;
    foo(a);
    rm.unlock();
}

int main(void)
{
    console::setupConsoleEncoding();

    std::thread t1(foo, 10);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::thread t2(foo, 10);

    t1.join();
    t2.join();

    return 0;
}
