#include <functional>
#include <iostream>
#include <mutex>
#include <thread>

struct Account
{
    int balance = 10000;
    std::mutex mtx;
};

void transfer(Account& from, Account& to)
{
    for (int i = 0; i < 1000; ++i)
    {
        // Захват обоих мьютексов с предотвращением deadlock при их захвате.
        std::scoped_lock guard(from.mtx, to.mtx);
        --from.balance;
        ++to.balance;
    } // guard освобождает оба мьютекса на каждой итерации.
}

int main()
{
    Account first;
    Account second;

    // Аргументы идут в разном порядке; оба потока используют scoped_lock.
    std::thread t1(transfer, std::ref(first), std::ref(second));
    std::thread t2(transfer, std::ref(second), std::ref(first));
    t1.join();
    t2.join();

    // После join() потоки больше не изменяют счета.
    std::cout << "First: " << first.balance << '\n';
    std::cout << "Second: " << second.balance << '\n';
    std::cout << "Total: " << first.balance + second.balance << '\n';
    return first.balance == 10000 && second.balance == 10000 ? 0 : 1;
}
