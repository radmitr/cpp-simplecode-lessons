#include "../common/reflection.hpp"

template<class T> struct Box { T value; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        constexpr auto instance = ^^Box<int>;
        static_assert(std::meta::template_of(instance) == ^^Box);
        static_assert(std::meta::template_arguments_of(instance)[0] == ^^int);
        constexpr auto generated = std::meta::substitute(^^Box, {^^double});
        static_assert(generated == ^^Box<double>);
        typename [:generated:] box{2.5};
        check(box.value == 2.5, "template substitution failed");
        std::cout << "OK 16-templates\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
