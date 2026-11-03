// C++11 — std::recursive_mutex.
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

#include "../../common/console.hpp"

std::mutex m;
std::recursive_mutex rm;

void foo(int a)
{
    std::cout << a << " ";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    if (a <= 1)
    {
        std::cout << std::endl;
        return;
    }
    a--;
    foo(a);
}

int main(void)
{
    console::setupConsoleEncoding();

    // m.lock();
    // m.unlock();

    // m.lock();
    // m.lock();
    // m.unlock();

    // m.lock();
    // m.unlock();
    // m.lock();
    // m.unlock();

    // m.lock();
    // m.unlock();
    // m.unlock();

    rm.lock();
    rm.lock();
    rm.lock();
    rm.unlock();
    rm.unlock();
    rm.unlock();

    std::cout << "Successfully end" << std::endl;

    return 0;
}
