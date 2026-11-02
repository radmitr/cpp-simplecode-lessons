// C++11 — std::shared_ptr и захват указателя по значению.
#include <future>
#include <iostream>
#include <memory>
#include <thread>

struct Settings { int value = 42; };

int main()
{
    auto owner = std::make_shared<Settings>();
    std::weak_ptr<Settings> observer = owner;
    std::promise<void> release;
    auto gate = release.get_future();
    int received = 0;
    std::thread worker([owner, &gate, &received]() {
        gate.wait();
        received = owner->value;
    });
    owner.reset(); // У main владельца больше нет; копия в лямбде ещё есть.
    const bool keptAlive = !observer.expired();
    release.set_value();
    worker.join();
    std::cout << "Kept alive: " << std::boolalpha << keptAlive << "; received: " << received << '\n';
    return keptAlive && received == 42 ? 0 : 1;
}
