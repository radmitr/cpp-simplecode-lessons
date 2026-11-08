// C++20 — std::stop_source и общий запрос остановки.
#include <atomic>
#include <iostream>
#include <stop_token>
#include <thread>

int main()
{
    std::stop_source group;
    std::atomic<int> stopped{0};
    auto work = [&stopped](std::stop_token token) {
        while (!token.stop_requested())
            std::this_thread::yield();
        ++stopped;
    };
    // Лямбды без параметров получают именно group.get_token().
    // Встроенный источник остановки каждого jthread здесь не используется.
    std::jthread first([&]() { work(group.get_token()); });
    std::jthread second([&]() { work(group.get_token()); });
    const bool initialRequest = group.request_stop();
    const bool repeatedRequest = group.request_stop();
    first.join();
    second.join();
    std::cout << std::boolalpha << "First request: " << initialRequest
              << "; repeated: " << repeatedRequest << "; stopped: " << stopped.load() << '\n';
    return initialRequest && !repeatedRequest && stopped == 2 ? 0 : 1;
}
