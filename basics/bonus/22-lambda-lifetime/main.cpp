#include <memory>
#include "../common/check.hpp"

auto make_counter(int initial) { return [value = initial]() mutable { return ++value; }; }
struct Sample { int value; auto snapshot() const { return [*this] { return value; }; } };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        auto counter = make_counter(5);
        check(counter() == 6 && counter() == 7, "owned mutable state failed");
        auto owner = [value = std::make_unique<int>(9)] { return *value; };
        check(owner() == 9, "move capture failed");
        auto twice = [](auto value) { return value + value; };
        check(twice(3) == 6, "generic lambda failed");
        Sample original{10};
        auto snapshot = original.snapshot();
        original.value = 20;
        check(snapshot() == 10, "*this must capture a copy");
        std::cout << counter() << ' ' << owner() << '\n';
        std::cout << "OK 22-lambda-lifetime\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
