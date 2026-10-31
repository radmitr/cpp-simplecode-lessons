#include "../common/reflection.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(__cpp_impl_reflection >= 202506L);
        static_assert(std::meta::is_type(^^int));
        std::cout << "reflection enabled; GCC " << __GNUC__ << '\n';
        std::cout << "OK 06-toolchain\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
