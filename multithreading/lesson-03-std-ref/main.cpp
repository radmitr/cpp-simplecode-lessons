#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void doWork(int &a)
{
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Thread ID: " << this_thread::get_id() << " ============\tdoWork STARTED\t============" << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
    a = a * 2;
    cout << "Thread ID: " << this_thread::get_id() << " ============\tdoWork STOPPED\t============" << endl;
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
