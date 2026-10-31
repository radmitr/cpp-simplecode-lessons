#ifndef NETWORKING_RETRY_HPP
#define NETWORKING_RETRY_HPP

#include "../common/net.hpp"
#include <condition_variable>
#include <iostream>
#include <mutex>

class Cancelled : public std::runtime_error
{
public:
    Cancelled() : std::runtime_error("retry cancelled") {}
};

class RetryControl
{
public:
    void cancel()
    {
        {
            std::lock_guard<std::mutex> guard(mutex_);
            cancelled_ = true;
        }
        changed_.notify_all();
    }
    bool wait(std::chrono::milliseconds duration)
    {
        std::unique_lock<std::mutex> lock(mutex_);
        return changed_.wait_for(lock, duration, [&]() { return cancelled_; });
    }
private:
    std::mutex mutex_;
    std::condition_variable changed_;
    bool cancelled_ = false;
};

inline net::Socket connectWithRetry(std::uint16_t port, RetryControl& control)
{
    auto pause = std::chrono::milliseconds(100);
    for (int attempt = 1; attempt <= 6; ++attempt)
    {
        if (control.wait(std::chrono::milliseconds(0))) throw Cancelled();
        std::cout << "Attempt " << attempt << std::endl;
        try
        {
            return net::connectLoopback(port, net::after(std::chrono::milliseconds(100)));
        }
        catch (const std::exception& error)
        {
            std::cout << "Connection failed: " << error.what() << '\n';
            if (attempt == 6) throw;
        }
        if (control.wait(pause)) throw Cancelled();
        pause = std::min(pause * 2, std::chrono::milliseconds(800));
    }
    throw std::runtime_error("retry attempts exhausted");
}
#endif
