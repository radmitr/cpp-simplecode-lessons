// C++23 — std::stacktrace и stacktrace_entry.
#include <exception>
#include <iostream>
#include <stacktrace>
#include <version>

#if defined(__cpp_lib_stacktrace)

#include "../../../basics/bonus/common/check.hpp"

std::stacktrace snapshot() { return std::stacktrace::current(0, 16); }

int main()
{
    try
    {
        const auto trace = snapshot();
        check(trace.size() <= 16, "frame limit");
        std::cout << "frames: " << trace.size() << '\n';
        if (!trace.empty())
        {
            std::cout << trace[0].description() << '\n';
            std::cout << trace[0].source_file() << ':' << trace[0].source_line() << '\n';
        }
        const auto skipped = std::stacktrace::current(1, 4);
        check(skipped.size() <= 4, "skip and limit");
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
    std::cout << "UNAVAILABLE: io/bonus/23-stacktrace\n";
    return 77;
}
#endif
