#include "../common/reflection.hpp"

struct Data { int count; double weight; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Data data{2, 3.5};
        double total = 0;
        template for (constexpr auto member : std::define_static_array(std::meta::nonstatic_data_members_of(
            ^^Data, std::meta::access_context::unprivileged())))
        {
            total += data.[:member:];
            std::cout << std::meta::identifier_of(member) << '\n';
        }
        check(total == 5.5, "expansion failed");
        std::cout << "OK 13-expansion-statements\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
