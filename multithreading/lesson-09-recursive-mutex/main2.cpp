#include <iostream>
#include <mutex>
#include <thread>

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

    thread t1(foo, 10);
    this_thread::sleep_for(chrono::milliseconds(200));
    thread t2(foo, 10);

    t1.join();
    t2.join();

    return 0;
}
