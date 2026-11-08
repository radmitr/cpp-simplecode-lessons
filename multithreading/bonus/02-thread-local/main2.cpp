// C++11 — thread_local и уничтожение объекта при завершении потока.
#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> created{0};
std::atomic<int> destroyed{0};

struct State
{
    int calls = 0;
    State() { ++created; }
    ~State() { ++destroyed; }
};

State& state()
{
    thread_local State instance; // Создаётся при первом входе в этом потоке.
    return instance;
}

int main()
{
    int calls = 0;
    std::thread worker([&]() {
        ++state().calls;
        calls = ++state().calls;
    });
    worker.join(); // К этому моменту закончены и деструкторы thread_local.
    std::cout << "Created: " << created << "; destroyed: " << destroyed
              << "; calls: " << calls << '\n';
    return created == 1 && destroyed == 1 && calls == 2 ? 0 : 1;
}
