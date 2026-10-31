#include <tuple>
#include "../common/reflection.hpp"

struct Data { int id; std::string name; };
template<class T, std::size_t... I>
auto tie_fields_impl(T& object, std::index_sequence<I...>)
{
    constexpr auto members = std::define_static_array(std::meta::nonstatic_data_members_of(
        ^^T, std::meta::access_context::unprivileged()));
    return std::tie(object.[:members[I]:]...);
}
template<class T> auto tie_fields(T& object)
{
    constexpr auto count = std::meta::nonstatic_data_members_of(
        ^^T, std::meta::access_context::unprivileged()).size();
    return tie_fields_impl(object, std::make_index_sequence<count>{});
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Data data{7, "Ada"};
        auto fields = tie_fields(data);
        std::get<0>(fields) = 9;
        check(data.id == 9 && std::get<1>(fields) == "Ada", "tuple references failed");
        std::cout << data.id << ' ' << data.name << '\n';
        std::cout << "OK 26-struct-to-tuple\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
