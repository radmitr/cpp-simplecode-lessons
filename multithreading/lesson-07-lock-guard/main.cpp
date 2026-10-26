#include <iostream>
#include <mutex>
#include <thread>
#include "SimpleTimer.hpp"

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
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
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
