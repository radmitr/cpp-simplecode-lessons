// C++11 — передача аргументов в std::thread.
#include <chrono>
#include <cstddef>
#include <iostream>
#include <string>
#include <thread>

#include "../../common/console.hpp"

void doWork(int a, int b, std::string msg)
{
    std::cout << msg << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tdoWork STARTED\t============" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::cout << "a + b = " << a + b << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    std::cout << "Thread ID: " << std::this_thread::get_id() << " ============\tdoWork STOPPED\t============" << std::endl;
}

int main(void)
{
    console::setupConsoleEncoding();

    std::thread th(doWork, 2, 3, "our_message");

    for (std::size_t i = 0; true; i++)
    {
        std::cout << "Thread ID: " << std::this_thread::get_id() << "\tmain\t" << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }

    // Сюда выполнение не дойдёт: условие цикла выше всегда true.
    th.join();

    return 0;
}
