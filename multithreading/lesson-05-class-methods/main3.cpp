#include <iostream>
#include <thread>

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

    MyClass m;

    // thread t([&]() {
    //     m.doWork2(123);
    // });
    thread t(MyClass::doWork2, m, 123);

    for (size_t i = 0; i < 10; i++)
    {
        cout << "Thread ID: " << this_thread::get_id() << "\tmain\t" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    t.join();

    return 0;
}
