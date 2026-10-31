#include "../common/reflection.hpp"

namespace model { struct Item { int id; }; }
using Alias = model::Item;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        constexpr auto alias = ^^Alias;
        static_assert(std::meta::dealias(alias) == ^^model::Item);
        static_assert(std::meta::parent_of(^^model::Item) == ^^model);
        constexpr auto location = std::meta::source_location_of(^^model::Item);
        check(location.line() > 0, "source location missing");
        std::cout << std::meta::identifier_of(^^model::Item) << '\n';
        std::cout << std::meta::display_string_of(^^Alias) << '\n';
        std::cout << "OK 08-names-and-origins\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
