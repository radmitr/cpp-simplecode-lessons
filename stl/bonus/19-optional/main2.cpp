// C++17 — optional: emplace, время жизни и ленивый запасной результат.
#include <exception>
#include <iostream>
#include <optional>
#include <string>
#include <utility>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        int calls = 0;
        auto fallback = [&] { ++calls; return std::string("fallback"); };
        std::optional<std::string> text("Ada");
        auto eager = text.value_or(fallback());
        check(eager == "Ada" && calls == 1, "argument evaluated eagerly");
        const auto lazy = text ? *text : fallback();
        check(lazy == "Ada" && calls == 1, "conditional fallback");
        auto moved = std::move(text);
        check(text.has_value() && moved.value() == "Ada", "moving does not disengage source");
        text.emplace(3, 'x');
        check(text.value() == "xxx", "construct in place");
        text = std::nullopt;
        check(!text, "disengage");
        std::cout << eager << ' ' << moved.value() << ' ' << calls << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
