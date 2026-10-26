#include <iostream>
#include <mutex>
#include <thread>
#include "SimpleTimer.hpp"

using namespace std;

mutex mtx;

// void print(char ch)
// {
//     // this_thread::sleep_for(chrono::milliseconds(2000));
//     // unique_lock<mutex> ul(mtx);

//     unique_lock<mutex> ul(mtx, std::defer_lock);

//     this_thread::sleep_for(chrono::milliseconds(2000));

//     ul.lock();

//     for (size_t i = 0; i < 5; ++i)
//     {
//         for (size_t i = 0; i < 10; i++)
//         {
//             cout << ch;
//             this_thread::sleep_for(chrono::milliseconds(10));
//         }
//         cout << endl;
//     }
//     cout << endl;

//     ul.unlock();

//     this_thread::sleep_for(chrono::milliseconds(2000));
// }

void print(char ch)
{
    unique_lock<mutex> ul(mtx, std::defer_lock);

    this_thread::sleep_for(chrono::milliseconds(2000));

    ul.lock();

    for (size_t i = 0; i < 5; ++i)
    {
        for (size_t i = 0; i < 10; i++)
        {
            cout << ch;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << endl;
    }
    cout << endl;
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

    t1.join();
    t2.join();

    return 0;
}
