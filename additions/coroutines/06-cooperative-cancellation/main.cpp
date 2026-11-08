// C++20 — stop_token и отмена на точках приостановки.
#include <coroutine>
#include <exception>
#include <iostream>
#include <stop_token>

#include "../../../basics/additions/common/check.hpp"
#include "../common/task.hpp"

struct Guard
{
    int& cleaned;
    ~Guard() { ++cleaned; }
};
Task<int> count(std::stop_token token, int& steps, int& cleaned)
{
    Guard guard{cleaned};
    while (!token.stop_requested())
    {
        ++steps;
        co_await std::suspend_always{};
    }
    co_return steps;
}
int main()
{
    try
    {
        std::stop_source stop;
        int steps = 0;
        int cleaned = 0;
        auto task = count(stop.get_token(), steps, cleaned);
        task.resume();
        check(steps == 1 && cleaned == 0 && !task.done(), "first suspension");
        check(stop.request_stop() && !stop.request_stop(), "stop request is one-shot");
        check(!task.done(), "request does not resume coroutine");
        task.resume();
        check(task.done() && task.result() == 1 && cleaned == 1, "cooperative cleanup");
        {
            std::stop_source another;
            auto abandoned = count(another.get_token(), steps, cleaned);
            abandoned.resume();
        }
        check(cleaned == 2, "destroy suspended frame releases locals");
        std::cout << "steps=2 cleaned=2\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
