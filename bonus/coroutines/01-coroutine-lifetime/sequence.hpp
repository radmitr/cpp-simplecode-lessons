// C++20 — coroutine_handle, promise_type и приостановка корутины.
#pragma once
#include <coroutine>
#include <exception>
#include <stdexcept>
#include <utility>

class Sequence
{
public:
    struct promise_type;
    using Handle = std::coroutine_handle<promise_type>;
    struct promise_type
    {
        int current = 0;
        std::exception_ptr failure;
        Sequence get_return_object() { return Sequence(Handle::from_promise(*this)); }
        std::suspend_always initial_suspend() noexcept { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        std::suspend_always yield_value(int value) noexcept
        {
            current = value;
            return {};
        }
        void return_void() noexcept {}
        void unhandled_exception() noexcept { failure = std::current_exception(); }
    };
    explicit Sequence(Handle handle) noexcept : handle_(handle) {}
    Sequence(const Sequence&) = delete;
    Sequence& operator=(const Sequence&) = delete;
    Sequence(Sequence&& other) noexcept
        : handle_(std::exchange(other.handle_, {})), ready_(std::exchange(other.ready_, false)) {}
    Sequence& operator=(Sequence&& other) noexcept
    {
        if (this != &other)
        {
            if (handle_) handle_.destroy();
            handle_ = std::exchange(other.handle_, {});
            ready_ = std::exchange(other.ready_, false);
        }
        return *this;
    }
    ~Sequence() { if (handle_) handle_.destroy(); }
    bool next()
    {
        ready_ = false;
        if (!handle_ || handle_.done()) return false;
        handle_.resume();
        if (handle_.promise().failure) std::rethrow_exception(handle_.promise().failure);
        ready_ = !handle_.done();
        return ready_;
    }
    int value() const
    {
        if (!ready_) throw std::logic_error("resume to a value first");
        return handle_.promise().current;
    }
private:
    Handle handle_;
    bool ready_ = false;
};
