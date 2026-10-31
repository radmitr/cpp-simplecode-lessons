#include <functional>
#include "../common/reflection.hpp"

struct Record { int id; std::string name; };
template<class T> bool equal_fields(const T& a, const T& b)
{
    bool equal = true;
    template for (constexpr auto m : std::define_static_array(std::meta::nonstatic_data_members_of(
        ^^T, std::meta::access_context::unprivileged())))
        equal = equal && (a.[:m:] == b.[:m:]);
    return equal;
}
template<class T> void copy_fields(const T& from, T& to)
{
    template for (constexpr auto m : std::define_static_array(std::meta::nonstatic_data_members_of(
        ^^T, std::meta::access_context::unprivileged()))) to.[:m:] = from.[:m:];
}
template<class T> std::size_t hash_fields(const T& object)
{
    std::size_t result = 0;
    reflection_demo::for_each_field(object, [&](auto, const auto& field) {
        using F = std::remove_cvref_t<decltype(field)>;
        result ^= std::hash<F>{}(field) + 0x9e3779b9u + (result << 6) + (result >> 2);
    });
    return result;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Record first{7, "Ada"}, second{7, "Ada"};
        check(equal_fields(first, second), "equal fields expected");
        check(hash_fields(first) == hash_fields(second), "equal records must have equal hashes");
        second.name = "Bob";
        check(!equal_fields(first, second), "different fields expected");
        copy_fields(first, second);
        check(equal_fields(first, second), "field copy failed");
        std::cout << "memberwise equality, hash and copy verified\n";
        std::cout << "OK 25-memberwise-operations\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
