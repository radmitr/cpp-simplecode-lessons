#include "../common/reflection.hpp"

struct Sample { int id; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        constexpr auto type = ^^Sample;
        constexpr auto member = ^^Sample::id;
        static_assert(std::meta::is_type(type));
        static_assert(std::meta::is_nonstatic_data_member(member));
        static_assert(std::meta::type_of(member) == ^^int);
        static_assert((type == ^^Sample) && (type != ^^int));
        std::cout << std::meta::identifier_of(type) << '\n';
        std::cout << "OK 07-reflection-info\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
