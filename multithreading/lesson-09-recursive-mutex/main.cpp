#include <iostream>
#include <mutex>
#include <thread>

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
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
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
