// C++26 — run_loop и starts_on; C++20 — std::jthread.
#include <exception>
#include <execution>
#include <iostream>
#include <thread>
#include <tuple>
#include <utility>
#include <version>

#if defined(__cpp_lib_execution) && __cpp_lib_execution >= 202406L

#include "../../../basics/bonus/common/check.hpp"

struct Finish
{
    std::execution::run_loop& loop;
    ~Finish() { loop.finish(); }
};

int main()
{
    try
    {
        std::execution::run_loop loop;
        std::jthread worker([&] { loop.run(); });
        Finish finish{loop};
        const auto caller = std::this_thread::get_id();
        auto work = std::execution::starts_on(loop.get_scheduler(), std::execution::just(5))
            | std::execution::then([caller](int x) {
                check(std::this_thread::get_id() != caller, "scheduler thread");
                return x + 1;
            });
        auto result = std::this_thread::sync_wait(std::move(work));
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
    std::cout << "UNAVAILABLE: bonus/execution/02-schedulers\n";
    return 77;
}
#endif
