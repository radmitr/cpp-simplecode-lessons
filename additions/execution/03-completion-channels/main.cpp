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
        auto value = execution_demo::sync_wait(ex::just(7));
        check(value && std::get<0>(*value) == 7, "value channel");
        auto stopped = execution_demo::sync_wait(execution_demo::MaybeValue{true, 0});
        check(!stopped, "stop is an empty optional");
        auto recovered = execution_demo::sync_wait(ex::just_error(5)
            | ex::upon_error([](int error) { return error + 3; }));
        check(recovered && std::get<0>(*recovered) == 8, "recover error into value");
        auto fallback = execution_demo::sync_wait(ex::just_stopped()
            | ex::upon_stopped([] { return 9; }));
        check(fallback && std::get<0>(*fallback) == 9, "recover stop into value");
        bool caught = false;
        try
        {
            execution_demo::sync_wait(ex::just() | ex::then([]() -> int {
                throw std::runtime_error("operation failed");
            }));
        }
        catch (const std::runtime_error&) { caught = true; }
        check(caught, "exception reaches sync_wait");
        std::cout << "7; stopped; 8; 9; exception\nOK reference-example\n";
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
