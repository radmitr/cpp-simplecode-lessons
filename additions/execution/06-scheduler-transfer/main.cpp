// C++26 — senders/receivers; внешний профиль stdexec использует C++20+.
#include <exception>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <tuple>
#include <utility>

#include "../../../basics/additions/common/check.hpp"
#include "../common.hpp"

#if CPP_EXECUTION_AVAILABLE
namespace ex = execution_demo::ex;

struct Context
{
    ex::run_loop loop;
    std::jthread worker;
    Context() : worker([this] { loop.run(); }) {}
    ~Context() { loop.finish(); worker.join(); }
};
int main()
{
    try
    {
        Context first;
        Context second;
        const auto first_id = first.worker.get_id();
        const auto second_id = second.worker.get_id();
        auto work = ex::starts_on(first.loop.get_scheduler(), ex::just(20))
            | ex::then([=](int value) {
                check(std::this_thread::get_id() == first_id, "first scheduler");
                return value + 1;
            })
            | ex::continues_on(second.loop.get_scheduler())
            | ex::then([=](int value) {
                check(std::this_thread::get_id() == second_id, "second scheduler");
                return value * 2;
            });
        auto result = execution_demo::sync_wait(std::move(work));
        check(result && std::get<0>(*result) == 42, "transferred result");
        std::cout << "42 across two schedulers\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}

#else
int main()
{
    std::cout << "UNAVAILABLE: C++26 execution; enable REFERENCE_LIBRARIES=1\n";
    return 77;
}
#endif
