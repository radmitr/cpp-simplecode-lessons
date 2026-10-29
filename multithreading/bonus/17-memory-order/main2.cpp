#include <atomic>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    struct Payload
    {
        int number = 0;
        std::string text;
    } payload;
    std::atomic<bool> ready{false};
    int received = 0;
    std::string receivedText;

    std::thread reader([&]() {
        while (!ready.load(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
        // acquire прочитал true от release: предыдущие записи писателя видны.
        received = payload.number;
        receivedText = payload.text;
        std::cout << "Received: " << received << ", " << receivedText << '\n';
    });
    std::thread writer([&]() {
        payload.number = 42;
        payload.text = "ready data";
        ready.store(true, std::memory_order_release);
        // После публикации payload больше не меняется.
    });

    writer.join();
    reader.join();
    return received == 42 && receivedText == "ready data" ? 0 : 1;
}
