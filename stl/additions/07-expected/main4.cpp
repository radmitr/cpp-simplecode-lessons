// C++23 — and_then/transform/or_else для std::optional; C++17 — optional.
#include <exception>
#include <iostream>
#include <optional>
#include <string>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::optional<int> input = 3;
        int calls = 0;
        auto twice = [&](int x) { ++calls; return x * 2; };
        auto result = input.transform(twice).and_then([](int x) -> std::optional<std::string> {
            if (x > 5) return std::to_string(x);
            return std::nullopt;
        });
        check(result.value() == "6" && calls == 1, "optional chain");
        input.reset();
        auto recovered = input.transform(twice).or_else([] { return std::optional{9}; });
        check(recovered.value() == 9 && calls == 1, "lazy empty branch");
        std::cout << result.value() << ' ' << recovered.value() << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
