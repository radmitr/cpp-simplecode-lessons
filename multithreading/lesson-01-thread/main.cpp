#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void doWork()
{
    for (size_t i = 0; i < 10; i++)
    {
        cout << "Thread ID: " << this_thread::get_id() << "\tdoWork\t" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
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
    cout << "START MAIN" << endl;

    thread th(doWork);
    thread th2(doWork);
    // th.detach();
    // th2.detach();

    for (size_t i = 0; i < 10; i++)
    {
        cout << "Thread ID: " << this_thread::get_id() << "\tmain\t" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    th.join();
    th2.join();

    cout << "END MAIN" << endl;
    return 0;
}
