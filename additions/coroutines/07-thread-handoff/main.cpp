// C++20 — корутины, binary_semaphore и jthread.
#include <coroutine>
#include <exception>
#include <iostream>
#include <semaphore>
#include <thread>

#include "../../../basics/additions/common/check.hpp"
#include "../common/task.hpp"

struct Handoff
{
    std::coroutine_handle<>& pending;
    std::binary_semaphore& ready;
    bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<> handle) const noexcept
    {
        pending = handle;
        // После публикации handle другой поток вправе уничтожить awaiter.
        ready.release();
    }
    void await_resume() const noexcept {}
};
Task<int> work(std::coroutine_handle<>& pending, std::binary_semaphore& ready,
               const std::thread::id caller)
{
    co_await Handoff{pending, ready};
    check(std::this_thread::get_id() != caller, "continued on worker");
    co_return 42;
}
int main()
{
    try
    {
        std::coroutine_handle<> pending;
        std::binary_semaphore ready(0);
        auto task = work(pending, ready, std::this_thread::get_id());
        std::jthread worker([&] {
            ready.acquire();
            const auto handle = pending;
            handle.resume();
        });
        task.resume();
        worker.join();
        check(task.done() && task.result() == 42, "join before reading/destroying frame");
        std::cout << "42 on worker\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
