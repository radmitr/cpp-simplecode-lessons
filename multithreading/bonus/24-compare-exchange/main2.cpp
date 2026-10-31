#include <atomic>
#include <iostream>
#include <thread>

bool reserveOne(std::atomic<int>& stock)
{
    int expected = stock.load();
    while (expected > 0)
    {
        if (stock.compare_exchange_weak(expected, expected - 1))
        {
            return true;
        }
        // При неудаче CAS записывает актуальное значение stock в expected.
        // weak может отказать и при совпадении: поэтому используем цикл.
    }
    return false;
}

int main()
{
    constexpr int initialStock = 1000;
    std::atomic<int> stock{initialStock};
    std::atomic<int> accepted{0};

    auto buyer = [&]() {
        for (int i = 0; i < 500; ++i)
        {
            if (reserveOne(stock))
            {
                ++accepted;
            }
        }
    };

    std::thread t1(buyer);
    std::thread t2(buyer);
    std::thread t3(buyer);
    std::thread t4(buyer);
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "Purchase attempts: 2000\n";
    std::cout << "Accepted orders: " << accepted.load() << '\n';
    std::cout << "Remaining items: " << stock.load() << '\n';
    return accepted.load() == initialStock && stock.load() == 0 ? 0 : 1;
}
