// C++17 — any: копирование, emplace и ссылочный доступ.
#include <any>
#include <exception>
#include <iostream>
#include <string>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        auto original = std::make_any<std::string>(3, 'a');
        auto copy = original;
        std::any_cast<std::string&>(copy)[0] = 'b';
        check(std::any_cast<const std::string&>(original) == "aaa", "independent copy");
        check(std::any_cast<const std::string&>(copy) == "baa", "reference access");
        copy.emplace<int>(42);
        check(std::any_cast<int>(copy) == 42, "replace stored type");
        std::cout << std::any_cast<const std::string&>(original) << ' ' << std::any_cast<int>(copy) << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
