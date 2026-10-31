#include <typeinfo>
#include <typeindex>
#include <map>
#include <string>
#include "../common/check.hpp"

struct Base { virtual ~Base() = default; };
struct Derived : Base {};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Derived derived;
        Base& base = derived;
        check(typeid(base) == typeid(Derived), "dynamic type expected");
        check(typeid(&base) == typeid(Base*), "pointer type is static");
        std::map<std::type_index, std::string> names;
        names.emplace(typeid(Derived), "derived");
        check(names.at(typeid(base)) == "derived", "type_index lookup failed");
        std::cout << "dynamic type name: " << typeid(base).name() << '\n';
        std::cout << "OK 02-typeid-type-index\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
