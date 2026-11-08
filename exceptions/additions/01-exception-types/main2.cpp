// C++11 — std::stoi и std::bad_function_call; C++17 — std::optional, std::variant и std::any.
#include <any>
#include <exception>
#include <functional>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

template<class Exception, class Function>
bool expect(const char* name, Function action)
{
    try { action(); }
    catch (const Exception&) { std::cout << name << '\n'; return true; }
    return false;
}

int main()
{
    try
    {
        check(expect<std::out_of_range>("out_of_range: vector::at", [] {
            std::vector<int> values{1};
            (void)values.at(9); // operator[] здесь не проверяет границы!
        }), "at must throw");
        check(expect<std::invalid_argument>("invalid_argument: stoi", [] {
            (void)std::stoi("text");
        }), "stoi must reject text");
        check(expect<std::out_of_range>("out_of_range: stoi", [] {
            (void)std::stoi("999999999999999999999999999999999");
        }), "stoi must reject overflow");
        check(expect<std::bad_function_call>("bad_function_call", [] {
            std::function<void()> empty;
            empty();
        }), "empty function must throw");
        check(expect<std::bad_optional_access>("bad_optional_access", [] {
            std::optional<int> empty;
            (void)empty.value();
        }), "empty optional value must throw");
        check(expect<std::bad_variant_access>("bad_variant_access", [] {
            std::variant<int, std::string> value{7};
            (void)std::get<std::string>(value);
        }), "wrong variant alternative must throw");
        check(expect<std::bad_any_cast>("bad_any_cast", [] {
            std::any value = 7;
            (void)std::any_cast<std::string>(value);
        }), "wrong any type must throw");
        std::cout << "OK library-exceptions\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
