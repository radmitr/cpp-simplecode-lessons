#include "../common/reflection.hpp"

struct Left { int id = 1; };
struct Right { int id = 2; };
struct Derived : Left, Right { int own = 3; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Derived value;
        template for (constexpr auto base : std::define_static_array(std::meta::bases_of(
            ^^Derived, std::meta::access_context::unprivileged())))
        {
            std::cout << value.[:base:].id << '\n';
            value.[:base:].id += 1;
        }
        check(value.Left::id == 2 && value.Right::id == 3, "base splice failed");
        static_assert(std::meta::nonstatic_data_members_of(^^Derived, std::meta::access_context::unprivileged()).size() == 1);
        std::cout << "OK 14-base-subobjects\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
