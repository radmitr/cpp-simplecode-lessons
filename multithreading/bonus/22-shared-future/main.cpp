#include <future>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>

struct Settings
{
    int maxConnections;
    std::string server;
};

int main()
{
    std::promise<Settings> promise;
    std::shared_future<Settings> settings = promise.get_future().share();
    std::mutex outputMtx;

    // Захват по значению: у каждого потока своя копия shared_future,
    // но все эти копии ссылаются на один результат.
    auto worker = [settings, &outputMtx](int id) {
        const Settings& received = settings.get();
        std::lock_guard<std::mutex> guard(outputMtx);
        std::cout << "Worker " << id << ": " << received.server
                  << ", max connections = " << received.maxConnections << '\n';
    };

    std::thread t1(worker, 1);
    std::thread t2(worker, 2);
    std::thread t3(worker, 3);
    promise.set_value(Settings{4, "localhost"});

    t1.join();
    t2.join();
    t3.join();

    // В отличие от future::get(), shared_future::get() можно вызвать повторно.
    std::cout << "Main get #1: " << settings.get().maxConnections << '\n';
    std::cout << "Main get #2: " << settings.get().maxConnections << '\n';
    return settings.get().maxConnections == 4 ? 0 : 1;
}
