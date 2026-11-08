// C++20 — ленивые корутины, symmetric transfer и владение кадром.
#pragma once
#include <coroutine>
#include <exception>
#include <optional>
#include <stdexcept>
#include <utility>

template<class T>
class Task
{
public:
    struct promise_type;
    using Handle = std::coroutine_handle<promise_type>;
    struct promise_type
    {
        std::optional<T> value;
        std::exception_ptr error;
        std::coroutine_handle<> continuation = std::noop_coroutine();
        Task get_return_object() noexcept { return Task(Handle::from_promise(*this)); }
        std::suspend_always initial_suspend() noexcept { return {}; }
        struct Final
        {
            bool await_ready() const noexcept { return false; }
            std::coroutine_handle<> await_suspend(Handle h) const noexcept
            {
                return h.promise().continuation;
            }
            void await_resume() const noexcept {}
        };
        Final final_suspend() noexcept { return {}; }
        void return_value(T result) { value.emplace(std::move(result)); }
        void unhandled_exception() noexcept { error = std::current_exception(); }
    };
    explicit Task(Handle handle) noexcept : handle_(handle) {}
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task(Task&& other) noexcept : handle_(std::exchange(other.handle_, {})) {}
    Task& operator=(Task&&) = delete;
    ~Task() { if (handle_) handle_.destroy(); }
    void resume()
    {
        if (!handle_ || handle_.done()) throw std::logic_error("task is not resumable");
        handle_.resume();
    }
    bool done() const noexcept { return handle_ && handle_.done(); }
    T result()
    {
        if (!done()) throw std::logic_error("task is not completed");
        return take(handle_);
    }
    struct Awaiter
    {
        Handle handle;
        Awaiter(const Awaiter&) = delete;
        explicit Awaiter(Handle h) noexcept : handle(h) {}
        ~Awaiter() { if (handle) handle.destroy(); }
        bool await_ready() const noexcept { return !handle || handle.done(); }
        std::coroutine_handle<> await_suspend(std::coroutine_handle<> parent) noexcept
        {
            handle.promise().continuation = parent;
            return handle;
        }
        T await_resume()
        {
            if (!handle) throw std::logic_error("empty task");
            return take(handle);
        }
    };
    Awaiter operator co_await() && noexcept { return Awaiter(std::exchange(handle_, {})); }
private:
    static T take(Handle handle)
    {
        if (handle.promise().error) std::rethrow_exception(handle.promise().error);
        if (!handle.promise().value) throw std::logic_error("missing result");
        return std::move(*handle.promise().value);
    }
    Handle handle_;
};
