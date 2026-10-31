#include <atomic>
#include <iostream>
#include <mutex>
#include <thread>

int main()
{
    std::atomic<int> stock{1};
    std::atomic<int> accepted{0};
    std::mutex outputMtx;

    auto buyLastItem = [&](int id) {
        int expected = 1; // Локальная переменная каждого покупателя.
        // Атомарно: если stock равен 1, заменить его на 0.
        const bool bought = stock.compare_exchange_strong(expected, 0);
        if (bought)
        {
            ++accepted;
        }

        std::lock_guard<std::mutex> guard(outputMtx);
        std::cout << "Buyer " << id << ": "
                  << (bought ? "accepted" : "rejected")
                  << "; expected after CAS = " << expected << '\n';
    };

    std::thread t1(buyLastItem, 1);
    std::thread t2(buyLastItem, 2);
    t1.join();
    t2.join();

    std::cout << "Accepted orders: " << accepted.load() << '\n';
    std::cout << "Remaining items: " << stock.load() << '\n';
    return accepted.load() == 1 && stock.load() == 0 ? 0 : 1;
}
