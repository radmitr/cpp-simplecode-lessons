// C++17 — std::scoped_lock с одним мьютексом и без мьютексов.
#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx1;
std::mutex mtx2;

void print(char symbol, bool reverse)
{
    for (int row = 0; row < 2; ++row)
    {
        if (reverse)
        {
            std::scoped_lock guard(mtx2, mtx1);
            std::cout << symbol << symbol << symbol << '\n';
        }
        else
        {
            std::scoped_lock guard(mtx1, mtx2);
            std::cout << symbol << symbol << symbol << '\n';
        }
    }
}

int main()
{
    // scoped_lock согласует захват пары, даже если аргументы переставлены.
    // Ручные lock() из main.cpp при таком порядке могли бы создать deadlock.
    std::thread first(print, '*', false);
    std::thread second(print, '#', true);
    first.join();
    second.join();
    std::cout << "Both threads completed\n";
}
