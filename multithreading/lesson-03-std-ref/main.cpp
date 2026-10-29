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

void doWork(int &a)
{
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Thread ID: " << this_thread::get_id() << " ============\tdoWork STARTED\t============" << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
    a = a * 2;
    cout << "Thread ID: " << this_thread::get_id() << " ============\tdoWork STOPPED\t============" << endl;
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

    int q = 5;

    thread th(doWork, std::ref(q));

    for (size_t i = 0; i < 10; i++)
    {
        cout << "Thread ID: " << this_thread::get_id() << "\tmain\t" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    th.join();
    cout << "q=" << q << endl;

    return 0;
}
