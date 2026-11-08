// C++23 — монадические операции std::expected.
#include <charconv>
#include <exception>
#include <expected>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>

#include "../../../basics/additions/common/check.hpp"

std::expected<int, std::string> parse(std::string_view text)
{
    if (text.empty()) return std::unexpected(std::string("empty"));
    int value = 0;
    auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), value);
    if (error != std::errc{} || end != text.data() + text.size()) return std::unexpected(std::string("format"));
    return value;
}
std::expected<int, std::string> positive(int x)
{
    if (x <= 0) return std::unexpected(std::string("positive"));
    return x;
}

int main()
{
    try
    {
        auto calculate = [](std::string_view text) {
            return parse(text).and_then(positive).transform([](int x) { return x * 2; })
                .transform_error([](const std::string& error) { return "input: " + error; });
        };
        check(calculate(std::string_view{}).error() == "input: empty", "empty input");
        check(calculate("999999999999999999999999").error() == "input: format", "overflow input");
        check(calculate("5").value() == 10, "success chain");
        check(calculate("bad").error() == "input: format", "parse error");
        check(calculate("0").error() == "input: positive", "validation error");
        auto recovered = calculate("bad").or_else([](const std::string&) -> std::expected<int, std::string> { return 7; });
        check(recovered.value() == 7, "recovery");
        std::cout << calculate("5").value() << ' ' << recovered.value() << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
