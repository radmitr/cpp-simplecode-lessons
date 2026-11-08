// C++11 — std::weak_ptr::lock().
// C++17 — проверяемый доступ к std::optional, std::variant и std::any.
#include <any>
#include <exception>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <variant>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::optional<int> absent;
        check(!absent.has_value(), "optional must be empty");
        std::variant<int, std::string> value{7};
        const std::string* wrongAlternative = std::get_if<std::string>(&value);
        const int* present = std::get_if<int>(&value);
        std::any boxed = 7;
        const std::string* wrongType = std::any_cast<std::string>(&boxed);
        std::weak_ptr<int> expired;
        const auto owner = expired.lock();
        check(!wrongAlternative && present && *present == 7 && !wrongType && !owner,
              "checked alternatives failed");
        std::cout << "optional empty; get_if/any_cast mismatch; weak_ptr expired\n";
        std::cout << "OK checked-access\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
