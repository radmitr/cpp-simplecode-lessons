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

mutex mtx;

void print(char ch)
{
    this_thread::sleep_for(chrono::milliseconds(2000));

    {
        lock_guard<mutex> guard(mtx);
        for (size_t i = 0; i < 5; ++i)
        {
            for (size_t i = 0; i < 10; i++)
            {
                cout << ch;
                this_thread::sleep_for(chrono::milliseconds(20));
            }
            cout << endl;
        }
        cout << endl;
    }

    this_thread::sleep_for(chrono::milliseconds(2000));
}

int main(void)
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    SimpleTimer timer;

    thread t1(print, '*');
    thread t2(print, '#');
    thread t3(print, '@');

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
