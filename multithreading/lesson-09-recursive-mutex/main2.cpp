#include <iostream>
#include <mutex>
#include <thread>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#endif

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

    std::thread t1(foo, 10);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::thread t2(foo, 10);

    t1.join();
    t2.join();

    return 0;
}
