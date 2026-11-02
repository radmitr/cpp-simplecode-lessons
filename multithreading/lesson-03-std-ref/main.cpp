// C++11 — std::ref и передача ссылки в std::thread.
#include <iostream>
#include <cstddef>
#include <thread>
#include <chrono>

#include "../../common/console.hpp"

void doWork(int &a)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tdoWork STARTED\t============" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    a = a * 2;
    std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tdoWork STOPPED\t============" << std::endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    int q = 5;

    std::thread th(doWork, std::ref(q));

    for (std::size_t i = 0; i < 10; i++)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << "\tmain\t" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    th.join();
    std::cout << "q=" << q << std::endl;

    return 0;
}
