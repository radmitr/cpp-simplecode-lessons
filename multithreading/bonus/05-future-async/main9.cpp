#include <future>
#include <iostream>
#include <thread>

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    int value = 0;
    std::thread worker([&value]() { value = sum(2, 5); });
    // Пока поток работает, main не читает value.
    worker.join();
    std::cout << "thread and join: " << value << '\n';

    auto result = std::async(std::launch::async, sum, 2, 5);
    const int received = result.get();
    std::cout << "async and get: " << received << '\n';
    return value == 7 && received == 7 ? 0 : 1;
}
