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

int main()
{
    try
    {
        auto combined = ex::when_all(ex::just(2), ex::just(3))
            | ex::then([](int left, int right) { return left + right; });
        auto sum = execution_demo::sync_wait(std::move(combined));
        check(sum && std::get<0>(*sum) == 5, "join values");
        auto dependent = ex::just(7) | ex::let_value([](int& value) {
            return ex::just(value * 6);
        });
        auto answer = execution_demo::sync_wait(std::move(dependent));
        check(answer && std::get<0>(*answer) == 42, "dependent sender");
        auto cancelled = execution_demo::sync_wait(ex::when_all(ex::just(1), execution_demo::MaybeValue{true, 0}));
        check(!cancelled, "combined stop");
        std::cout << "5 42 stopped\nOK reference-example\n";
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
