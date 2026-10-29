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

using namespace std;

recursive_mutex rm;

void foo(int a)
{
    rm.lock();
    cout << a << " ";
    this_thread::sleep_for(chrono::milliseconds(300));

    if (a <= 1)
    {
        cout << endl;
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

    thread t1(foo, 10);
    this_thread::sleep_for(chrono::milliseconds(200));
    thread t2(foo, 10);

    t1.join();
    t2.join();

    return 0;
}
