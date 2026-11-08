// C++17 — std::from_chars; C++23 — std::expected и std::unexpected.
#include <charconv>
#include <expected>
#include <iostream>
#include <string>
#include <string_view>
#include <system_error>

std::expected<int, std::string> parsePositive(std::string_view text)
{
    if (text.empty())
        return std::unexpected(std::string("not an integer"));
    int value = 0;
    const auto result = std::from_chars(text.data(), text.data() + text.size(), value);
    if (result.ec != std::errc{} || result.ptr != text.data() + text.size())
        return std::unexpected(std::string("not an integer"));
    if (value <= 0)
        return std::unexpected(std::string("must be positive"));
    return value;
}

int main()
{
    bool correct = !parsePositive(std::string_view{}).has_value();
    for (std::string_view text : {"12", "12abc", "-3"})
    {
        auto result = parsePositive(text);
        if (result)
            std::cout << text << " -> " << *result << '\n'; // Проверка уже выполнена.
        else
            std::cout << text << " -> " << result.error() << '\n';
        correct = correct && (result.has_value() == (text == "12"));
    }
    return correct ? 0 : 1;
}
