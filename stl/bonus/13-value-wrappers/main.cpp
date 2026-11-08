// C++26 — std::indirect.
#include <exception>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <version>

#if defined(__cpp_lib_indirect)

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::indirect<std::string> original(std::in_place, "one");
        auto copy = original;
        *copy = "two";
        check(*original == "one" && *copy == "two", "deep copy");
        std::cout << *original << ' ' << *copy << '\n';
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
    std::cout << "UNAVAILABLE: stl/bonus/13-value-wrappers\n";
    return 77;
}
#endif
