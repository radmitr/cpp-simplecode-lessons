// C++20 — await_ready, await_suspend и await_resume.
#include <coroutine>
#include <exception>
#include <iostream>
#include <utility>
#include <vector>

#include "../../../basics/additions/common/check.hpp"
#include "../common/task.hpp"

struct Pause
{
    std::coroutine_handle<>& pending;
    std::vector<int>& events;
    bool await_ready() const noexcept { return false; }
    void await_suspend(std::coroutine_handle<> handle) noexcept { pending = handle; }
    int await_resume() { events.push_back(2); return 21; }
};
struct Immediate
{
    bool await_ready() const noexcept { return true; }
    void await_suspend(std::coroutine_handle<>) const noexcept { std::terminate(); }
    int await_resume() const noexcept { return 1; }
};
struct NoPause
{
    bool await_ready() const noexcept { return false; }
    bool await_suspend(std::coroutine_handle<>) const noexcept { return false; }
    int await_resume() const noexcept { return 20; }
};
Task<int> calculate(std::coroutine_handle<>& pending, std::vector<int>& events)
{
    events.push_back(1);
    const int first = co_await Immediate{};
    const int second = co_await NoPause{};
    const int third = co_await Pause{pending, events};
    co_return first + second + third;
}
int main()
{
    try
    {
        std::coroutine_handle<> pending;
        std::vector<int> events;
        auto task = calculate(pending, events);
        check(events.empty(), "lazy start");
        task.resume();
        check(!task.done() && pending && events == std::vector{1}, "suspended");
        auto resume = std::exchange(pending, {});
        resume.resume();
        check(task.done() && task.result() == 42 && events == std::vector({1, 2}), "resumed");
        std::cout << "42\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
