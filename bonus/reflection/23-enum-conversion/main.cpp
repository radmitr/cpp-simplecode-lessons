#include "../common/reflection.hpp"

enum class Color { red, green, blue };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        using namespace reflection_demo;
        check(enum_name(Color::green) == "green", "enum to string failed");
        check(enum_value<Color>("blue") == Color::blue, "string to enum failed");
        check(!enum_value<Color>("BLUE"), "comparison must be case-sensitive");
        check(enum_name(static_cast<Color>(99)).empty(), "unknown value expected");
        std::cout << enum_name(Color::green) << '\n';
        std::cout << "OK 23-enum-conversion\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
