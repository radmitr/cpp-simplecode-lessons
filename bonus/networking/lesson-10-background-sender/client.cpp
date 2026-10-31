#include "../common/net.hpp"

#include <condition_variable>
#include <exception>
#include <iostream>
#include <mutex>
#include <thread>

class LatestSender
{
public:
    explicit LatestSender(std::uint16_t port) : worker_([this, port]() { run(port); }) {}
    ~LatestSender() { stopAndJoin(); }
    LatestSender(const LatestSender&) = delete;
    LatestSender& operator=(const LatestSender&) = delete;

    void update(std::string message)
    {
        {
            std::lock_guard<std::mutex> guard(mutex_);
            if (stopped_) throw std::runtime_error("sender is already stopped");
            latest_ = std::move(message);
            pending_ = true;
        }
        changed_.notify_one();
    }

    void finish()
    {
        stopAndJoin();
        if (failure_) std::rethrow_exception(failure_); // Читаем после join().
    }

private:
    void stopAndJoin()
    {
        {
            std::lock_guard<std::mutex> guard(mutex_);
            stopped_ = true;
        }
        changed_.notify_one();
        if (worker_.joinable()) worker_.join();
    }

    void run(std::uint16_t port)
    {
        try
        {
            auto socket = net::connectLoopback(port, net::after(std::chrono::seconds(2)));
            for (;;)
            {
                std::string message;
                {
                    std::unique_lock<std::mutex> lock(mutex_);
                    changed_.wait(lock, [&]() { return stopped_ || pending_; });
                    if (stopped_ && !pending_) break; // Последнее обновление отправляем перед выходом.
                    message = std::move(latest_);
                    pending_ = false;
                } // Освобождаем mutex до сетевой операции.
                net::sendAll(socket, message + '\n', net::after(std::chrono::seconds(2)));
            }
        }
        catch (...)
        {
            failure_ = std::current_exception(); // Исключение не покидает функцию потока.
        }
    }

    std::mutex mutex_;
    std::condition_variable changed_;
    std::string latest_;
    bool pending_ = false;
    bool stopped_ = false;
    std::exception_ptr failure_;
    std::thread worker_; // Создаётся после остальных полей.
};

int main(int argc, char* argv[])
{
    try
    {
        net::Runtime runtime;
        LatestSender sender(net::portArgument(argc, argv, 42010));
        sender.update("value=1");
        sender.update("value=2");
        sender.update("value=3");
        std::cout << "Main can do independent work\n";
        sender.finish();
        std::cout << "Sender finished; latest value delivered to the TCP stream\n";
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << '\n';
        return 1;
    }
}
