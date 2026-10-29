#include <iostream>
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

using namespace std;

mutex mtx1;
mutex mtx2;

void print()
{
    // mtx2.lock();
    // this_thread::sleep_for(chrono::milliseconds(1));
    // mtx1.lock();

    mtx1.lock();
    this_thread::sleep_for(chrono::milliseconds(1));
    mtx2.lock();

    for (size_t i = 0; i < 5; ++i)
    {
        for (size_t i = 0; i < 10; i++)
        {
            cout << '*';
            this_thread::sleep_for(chrono::milliseconds(20));
        }
        cout << endl;
    }
    cout << endl;

    // mtx1.unlock();
    // mtx2.unlock();

    mtx2.unlock();
    mtx1.unlock();
}

void print2()
{
    mtx1.lock();
    this_thread::sleep_for(chrono::milliseconds(1));
    mtx2.lock();

    for (size_t i = 0; i < 5; ++i)
    {
        for (size_t i = 0; i < 10; i++)
        {
            cout << '#';
            this_thread::sleep_for(chrono::milliseconds(20));
        }
        cout << endl;
    }
    cout << endl;

    mtx2.unlock();
    mtx1.unlock();
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

    thread t1(print);
    thread t2(print2);

    t1.join();
    t2.join();

    return 0;
}
