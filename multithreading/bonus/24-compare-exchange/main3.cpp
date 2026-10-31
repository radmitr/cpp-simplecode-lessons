#include <atomic>
#include <future>
#include <iostream>
#include <thread>

int main()
{
    std::atomic<int> stock{1};
    std::atomic<int> accepted{0};
    std::promise<void> checked[2];
    std::shared_future<void> signals[]{
        checked[0].get_future().share(),
        checked[1].get_future().share()
    };

    auto buy = [&](int id) {
        const bool available = stock.load() == 1;
        checked[id].set_value();
        signals[1 - id].wait(); // Оба покупателя уже прочитали исходный stock.
        if (available)
        {
            stock.store(0);
            ++accepted;
        }
    };

    std::thread first(buy, 0);
    std::thread second(buy, 1);
    first.join();
    second.join();
    std::cout << "Accepted with separate load/store: " << accepted.load() << '\n';
    std::cout << "Remaining items: " << stock.load() << '\n';
    // Это ожидаемая логическая ошибка, а не гонка данных: все обращения атомарны.
    return accepted.load() == 2 && stock.load() == 0 ? 0 : 1;
}
