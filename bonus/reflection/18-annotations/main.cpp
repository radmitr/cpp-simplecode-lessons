#include "../common/reflection.hpp"

struct Skip {};
struct Annotated { int visible; [[=Skip{}]] int internal; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Annotated object{10, 20};
        int included = 0;
        template for (constexpr auto member : std::define_static_array(std::meta::nonstatic_data_members_of(
            ^^Annotated, std::meta::access_context::unprivileged())))
        {
            if constexpr (std::meta::annotations_of_with_type(member, ^^Skip).empty())
            {
                included += object.[:member:];
                std::cout << std::meta::identifier_of(member) << '\n';
            }
        }
        check(included == 10, "skip annotation ignored");
        std::cout << "OK 18-annotations\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
