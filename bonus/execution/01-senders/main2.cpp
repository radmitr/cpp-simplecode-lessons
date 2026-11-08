// C++26 — let_value, just_error и upon_error.
#include <exception>
#include <execution>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <version>

#if defined(__cpp_lib_execution) && __cpp_lib_execution >= 202406L

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        auto nested = std::execution::just(4) | std::execution::let_value([](int& x) { return std::execution::just(x + 1); });
        auto result = std::this_thread::sync_wait(nested);
        check(result && std::get<0>(*result) == 5, "nested sender");
        auto recovered = std::execution::just_error(7) | std::execution::upon_error([](int error) { return error + 1; });
        auto repaired = std::this_thread::sync_wait(recovered);
        check(repaired && std::get<0>(*repaired) == 8, "error recovery");
        bool caught = false;
        try
        {
            auto failed = std::execution::just() | std::execution::then([]() -> int {
                throw std::runtime_error("operation error");
            });
            (void)std::this_thread::sync_wait(failed);
        }
        catch (const std::runtime_error&)
        {
            caught = true;
        }
        check(caught, "error completion");
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
    std::cout << "UNAVAILABLE: bonus/execution/01-senders\n";
    return 77;
}
#endif
