#include <iostream>
#include <thread>
#include <chrono>

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

void doWork(int a, int b, string msg)
{
    cout << msg << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "Thread ID: " << this_thread::get_id() << " ============\tdoWork STARTED\t============" << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
    cout << "a + b = " << a + b << endl;
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "Thread ID: " << this_thread::get_id() << " ============\tdoWork STOPPED\t============" << endl;
}

int main(void)
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    thread th(doWork, 2, 3, "our_message");

    for (size_t i = 0; true; i++)
    {
        cout << "Thread ID: " << this_thread::get_id() << "\tmain\t" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    th.join();

    return 0;
}
