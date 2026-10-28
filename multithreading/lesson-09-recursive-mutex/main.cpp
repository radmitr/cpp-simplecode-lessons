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

mutex m;
recursive_mutex rm;

void foo(int a)
{
    cout << a << " ";
    this_thread::sleep_for(chrono::milliseconds(500));

    if (a <= 1)
    {
        cout << endl;
        return;
    }
    a--;
    foo(a);
}

int main(void)
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

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

    cout << "Successfully end" << endl;

    return 0;
}
