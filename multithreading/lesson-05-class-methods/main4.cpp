#include <iostream>
#include <thread>
#include <functional>

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

class MyClass
{
public:
    void doWork()
    {
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout << "Thread ID: " << this_thread::get_id() << " ============\tdoWork STARTED\t============" << endl;
        this_thread::sleep_for(chrono::milliseconds(5000));
        cout << "Thread ID: " << this_thread::get_id() << " ============\tdoWork STOPPED\t============" << endl;
    }

    void doWork2(int a)
    {
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout << "Thread ID: " << this_thread::get_id() << " ============\tdoWork2 STARTED\t============" << endl;
        this_thread::sleep_for(chrono::milliseconds(5000));
        cout << "Thread ID: " << this_thread::get_id() << " doWork2 parameter: " << a << endl;
        cout << " ============\tdoWork2 STOPPED\t============" << endl;
    }

    int sum(int a, int b)
    {
        this_thread::sleep_for(chrono::milliseconds(2000));
        cout << "Thread ID: " << this_thread::get_id() << " ============\tsum STARTED\t============" << endl;
        this_thread::sleep_for(chrono::milliseconds(5000));
        cout << "Thread ID: " << this_thread::get_id() << " ============\tsum STOPPED\t============" << endl;
        return a + b;
    }
};

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

    MyClass m;

    thread t(&MyClass::doWork2, std::ref(m), 123);

    for (size_t i = 0; i < 10; i++)
    {
        cout << "Thread ID: " << this_thread::get_id() << "\tmain\t" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    t.join();

    return 0;
}
