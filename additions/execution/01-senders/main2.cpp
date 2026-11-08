// C++26 — let_value, just_error и upon_error.
#include <exception>
#include <execution>
#include <iostream>
#include <stdexcept>
#include <tuple>
#include <version>

#include "../common.hpp"

#if CPP_EXECUTION_AVAILABLE

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        auto nested = execution_demo::ex::just(4) | execution_demo::ex::let_value([](int& x) { return execution_demo::ex::just(x + 1); });
        auto result = execution_demo::sync_wait(nested);
        check(result && std::get<0>(*result) == 5, "nested sender");
        auto recovered = execution_demo::ex::just_error(7) | execution_demo::ex::upon_error([](int error) { return error + 1; });
        auto repaired = execution_demo::sync_wait(recovered);
        check(repaired && std::get<0>(*repaired) == 8, "error recovery");
        bool caught = false;
        try
        {
            auto failed = execution_demo::ex::just() | execution_demo::ex::then([]() -> int {
                throw std::runtime_error("operation error");
            });
            (void)execution_demo::sync_wait(failed);
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
    std::cout << "UNAVAILABLE: additions/execution/01-senders\n";
    return 77;
}
#endif
