#include <chrono>
#include <iostream>
#include <syncstream>
#include <thread>

int main()
{
    auto write = [](int id) {
        for (int number = 1; number <= 3; ++number)
        {
            // У каждого сообщения свой буфер, связанный с общим std::cout.
            std::osyncstream line(std::cout);
            line << "Worker " << id << ": ";
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            line << "message " << number << '\n';
        } // Деструктор line передаёт накопленное сообщение целиком.
    };

    std::thread t1(write, 1);
    std::thread t2(write, 2);
    std::thread t3(write, 3);
    t1.join();
    t2.join();
    t3.join();
    std::cout << "All 9 messages finished\n";
}
