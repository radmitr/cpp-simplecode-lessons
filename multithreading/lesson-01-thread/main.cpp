// C++11 — std::thread, join() и std::chrono.
#include <iostream>
#include <cstddef>
#include <thread>
#include <chrono>

#include "../../common/console.hpp"

void doWork()
{
    for (std::size_t i = 0; i < 10; i++)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << "\tdoWork\t" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main(void)
{
    console::setupConsoleEncoding();
    std::cout << "START MAIN" << std::endl;

    std::thread th(doWork);
    std::thread th2(doWork);
    // th.detach();
    // th2.detach();

    for (std::size_t i = 0; i < 10; i++)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << "\tmain\t" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    th.join();
    th2.join();

    std::cout << "END MAIN" << std::endl;
    return 0;
}
