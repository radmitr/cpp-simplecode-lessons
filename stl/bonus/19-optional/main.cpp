// C++17 — std::optional, nullopt, value и value_or.
#include <exception>
#include <iostream>
#include <optional>
#include <string>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::optional<int> value;
        check(!value, "initially empty");
        bool caught = false;
        try { (void)value.value(); }
        catch (const std::bad_optional_access&) { caught = true; }
        check(caught && value.value_or(9) == 9, "checked access and fallback");
        value = 0;
        check(value.has_value() && *value == 0, "zero is a present value");
        value.reset();
        check(!value, "reset");
        std::cout << value.value_or(9) << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
