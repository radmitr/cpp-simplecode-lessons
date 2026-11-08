// C++26 — run_loop и starts_on; C++20 — std::jthread.
#include <exception>
#include <execution>
#include <iostream>
#include <thread>
#include <tuple>
#include <utility>
#include <version>

#include "../common.hpp"

#if CPP_EXECUTION_AVAILABLE

#include "../../../basics/additions/common/check.hpp"

struct Finish
{
    execution_demo::ex::run_loop& loop;
    ~Finish() { loop.finish(); }
};

int main()
{
    try
    {
        execution_demo::ex::run_loop loop;
        std::jthread worker([&] { loop.run(); });
        Finish finish{loop};
        const auto caller = std::this_thread::get_id();
        auto work = execution_demo::ex::starts_on(loop.get_scheduler(), execution_demo::ex::just(5))
            | execution_demo::ex::then([caller](int x) {
                check(std::this_thread::get_id() != caller, "scheduler thread");
                return x + 1;
            });
        auto result = execution_demo::sync_wait(std::move(work));
        check(result && std::get<0>(*result) == 6, "scheduled result");
        std::cout << std::get<0>(*result) << '\n';
        std::cout << "OK modern-example\n";
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
    std::cout << "UNAVAILABLE: additions/execution/05-schedulers\n";
    return 77;
}
#endif
