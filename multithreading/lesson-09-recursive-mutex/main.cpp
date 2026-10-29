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
