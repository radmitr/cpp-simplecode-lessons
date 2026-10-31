#include <vector>
#include <memory>
#include <utility>
#include "../common/check.hpp"

struct Value { std::vector<int> values; }; // Правило нуля.
struct Owner {
    std::unique_ptr<int> value;
    explicit Owner(std::unique_ptr<int> data) : value(std::move(data)) {}
    Owner(const Owner&) = delete;
    Owner& operator=(const Owner&) = delete;
    Owner(Owner&&) noexcept = default;
    Owner& operator=(Owner&&) noexcept = default;
    ~Owner() = default;
};
Value make_value() { return Value{{1, 2, 3}}; }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Value first{{1, 2}};
        Value second = first;
        second.values[0] = 9;
        check(first.values[0] == 1, "copy must own independent data");
        Owner owner(std::make_unique<int>(7));
        Owner moved = std::move(owner);
        check(!owner.value && *moved.value == 7, "defaulted move failed");
        Value returned = make_value();
        check(returned.values.size() == 3, "return by value failed");
        std::cout << "independent copy; exclusive move; return by value\n";
        std::cout << "OK 10-rule-of-zero-five\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
