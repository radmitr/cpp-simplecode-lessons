// C++17 — std::any, any_cast и точное совпадение типа.
#include <any>
#include <exception>
#include <iostream>
#include <string>
#include <typeinfo>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::any value = 7;
        check(value.has_value() && value.type() == typeid(int), "stored type");
        int* number = std::any_cast<int>(&value);
        check(number && !std::any_cast<double>(&value), "no implicit conversion");
        *number = 9;
        const auto copy = std::any_cast<int>(value);
        check(copy == 9, "value access");
        bool caught = false;
        try { (void)std::any_cast<std::string>(value); }
        catch (const std::bad_any_cast&) { caught = true; }
        check(caught, "wrong type throws");
        value.reset();
        check(!value.has_value() && value.type() == typeid(void), "empty any");
        std::cout << copy << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
