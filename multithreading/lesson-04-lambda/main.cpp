#include <iostream>
#include <thread>

using namespace std;

int sum(int a, int b)
{
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Thread ID: " << this_thread::get_id() << " ============\tsum STARTED\t============" << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));
    cout << "Thread ID: " << this_thread::get_id() << " ============\tsum STOPPED\t============" << endl;
    return a + b;
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

    // int result = sum(2, 5);
    // cout << "Result: " << result << endl;

    // thread t(sum, 2, 5);

    // int result;
    // auto f = [&result]() { result = sum(2, 5); };
    // thread t(f);

    int result;
    thread t([&result]() { result = sum(2, 5); });

    for (size_t i = 0; i < 10; i++)
    {
        cout << "Thread ID: " << this_thread::get_id() << "\tmain\t" << i << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    t.join();

    cout << "sum result: " << result << endl;

    return 0;
}
