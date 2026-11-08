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

struct Receiver
{
    using receiver_concept = ex::receiver_tag;
    int& value;
    int& completions;
    auto get_env() const noexcept { return ex::env<>(); }
    void set_value(int result) && noexcept { value = result; ++completions; }
    void set_error(std::exception_ptr) && noexcept { std::terminate(); }
    void set_stopped() && noexcept { std::terminate(); }
};
int main()
{
    try
    {
        int value = 0;
        int completions = 0;
        auto sender = ex::just(42);
        auto operation = ex::connect(std::move(sender), Receiver{value, completions});
        check(value == 0 && completions == 0, "connect does not start work");
        ex::start(operation);
        check(value == 42 && completions == 1, "one value completion");
        std::cout << "42; completions=1\nOK reference-example\n";
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
