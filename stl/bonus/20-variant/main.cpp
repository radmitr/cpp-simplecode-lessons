// C++17 — variant, monostate, get_if и visit.
#include <exception>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <variant>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::variant<std::monostate, int, std::string> value;
        check(value.index() == 0 && std::holds_alternative<std::monostate>(value), "initial state");
        value = 7;
        check(std::get_if<int>(&value) && !std::get_if<std::string>(&value), "checked alternative");
        value.emplace<std::string>(3, 'x');
        auto describe = [](const auto& item) -> std::string {
            using T = std::decay_t<decltype(item)>;
            if constexpr (std::is_same_v<T, std::monostate>) return "empty";
            else if constexpr (std::is_same_v<T, int>) return std::to_string(item);
            else return item;
        };
        check(std::visit(describe, value) == "xxx", "visitor result");
        std::variant<int, int> repeated(std::in_place_index<1>, 9);
        check(repeated.index() == 1 && std::get<1>(repeated) == 9, "access repeated type by index");
        std::cout << std::visit(describe, value) << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
