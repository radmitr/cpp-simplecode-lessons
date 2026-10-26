#include <iostream>
#include <mutex>
#include <thread>
#include "SimpleTimer.hpp"

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

int main(void)
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
#endif

    SimpleTimer timer;

    thread t1(print);
    thread t2(print2);

    t1.join();
    t2.join();

    return 0;
}
