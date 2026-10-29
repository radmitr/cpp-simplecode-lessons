#include <atomic>
#include <iostream>
#include <thread>

int main()
{
    std::atomic<bool> ready{false};
    int payload = 0;
    int received = 0;

    std::thread worker([&]() {
        ready.wait(false); // Ждём, пока значение перестанет быть false.
        received = payload;
        std::cout << "Worker received: " << received << '\n';
    });

    payload = 42;
    ready.store(true); // Сначала изменяем состояние.
    ready.notify_one(); // Затем уведомляем ожидающего.
    worker.join();
    return received == 42 ? 0 : 1;
}
