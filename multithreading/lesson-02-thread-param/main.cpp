#include <iostream>
#include <thread>
#include <chrono>

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
    system("chcp 65001 > nul");
#else
    if (!setlocale(LC_ALL, "ru_RU.UTF-8"))
    {
        setlocale(LC_ALL, "");
    }
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
