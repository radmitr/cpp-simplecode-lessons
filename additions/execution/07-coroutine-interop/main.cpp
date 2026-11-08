// C++20 — корутины; NVIDIA stdexec — внешний task, не стандартный std::task.
#include <exception>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <utility>

#include "../../../basics/additions/common/check.hpp"
#include "../common.hpp"

#if defined(CPP_USE_STDEXEC)
stdexec::task<int> answer()
{
    const int value = co_await stdexec::just(21);
    co_return value * 2;
}
stdexec::task<int> failure()
{
    co_await (stdexec::just() | stdexec::then([] { throw std::runtime_error("awaited error"); }));
    co_return 0;
}
int main()
{
    try
    {
        auto value = stdexec::sync_wait(answer());
        check(value && std::get<0>(*value) == 42, "sender awaited in a supported task");
        bool caught = false;
        try { stdexec::sync_wait(failure()); }
        catch (const std::runtime_error&) { caught = true; }
        check(caught, "awaited failure propagated");
        std::cout << "42; awaited error\nOK reference-example\n";
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
    std::cout << "UNAVAILABLE: this example explicitly needs NVIDIA stdexec; enable REFERENCE_LIBRARIES=1\n";
    return 77;
}
#endif
