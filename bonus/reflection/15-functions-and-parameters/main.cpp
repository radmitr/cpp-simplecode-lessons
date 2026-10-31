#include "../common/reflection.hpp"

int scale(int value, int factor = 2) noexcept { return value * factor; }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        constexpr auto function = ^^scale;
        static_assert(std::meta::is_function(function));
        static_assert(std::meta::is_noexcept(function));
        static_assert(std::meta::return_type_of(function) == ^^int);
        static_assert(std::meta::parameters_of(function).size() == 2);
        template for (constexpr auto parameter : std::define_static_array(std::meta::parameters_of(function)))
            std::cout << std::meta::identifier_of(parameter) << '\n';
        check([:function:](3, 4) == 12, "reflected call failed");
        std::cout << "OK 15-functions-and-parameters\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
