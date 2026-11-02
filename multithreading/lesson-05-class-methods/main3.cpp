// C++11 — вызов метода объекта через std::thread.
#include <iostream>
#include <cstddef>
#include <thread>

#include "../../common/console.hpp"

class MyClass
{
public:
    void doWork()
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tdoWork STARTED\t============" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tdoWork STOPPED\t============" << std::endl;
    }

    void doWork2(int a)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tdoWork2 STARTED\t============" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "Thread ID: " << std::this_thread::get_id() << " doWork2 parameter: " << a << std::endl;
        std::cout << " ============\tdoWork2 STOPPED\t============" << std::endl;
    }

    int sum(int a, int b)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tsum STARTED\t============" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tsum STOPPED\t============" << std::endl;
        return a + b;
    }
};

int main(void)
{
    console::setupConsoleEncoding();

    MyClass m;

    // std::thread t([&]() {
    //     m.doWork2(123);
    // });
    std::thread t(&MyClass::doWork2, m, 123);

    for (std::size_t i = 0; i < 10; i++)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << "\tmain\t" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    t.join();

    return 0;
}
