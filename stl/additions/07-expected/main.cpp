// C++23 — std::expected, std::unexpected и std::bad_expected_access.
#include <expected>
#include <iostream>
#include <string>

int main()
{
    std::expected<int, std::string> success = 42;
    std::expected<int, std::string> failure = std::unexpected(std::string("invalid number"));
    std::cout << "Value: " << success.value() << '\n';
    if (!failure)
        std::cout << "Error: " << failure.error() << '\n';
    bool caught = false;
    try
    {
        (void)failure.value(); // value() проверяет состояние и бросает исключение.
    }
    catch (const std::bad_expected_access<std::string>& error)
    {
        caught = error.error() == "invalid number";
        std::cout << "Caught: " << error.error() << '\n';
    }
    std::cout << "Fallback: " << failure.value_or(0) << '\n';
    return caught && success == 42 && !failure ? 0 : 1;
}
