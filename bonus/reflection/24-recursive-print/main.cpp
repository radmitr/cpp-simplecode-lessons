#include <sstream>
#include "../common/reflection.hpp"

struct Address { int zip; };
struct Person { int id; Address address; };
template<class T> void print_record(std::ostream& out, const T& object)
{
    if constexpr (requires { out << object; }) out << object;
    else
    {
        out << '{'; bool first = true;
        reflection_demo::for_each_field(object, [&](auto name, const auto& field) {
            if (!first) out << ',';
            first = false; out << name << '=';
            print_record(out, field);
        });
        out << '}';
    }
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Person person{7, {10}};
        std::ostringstream output;
        print_record(output, person);
        check(output.str() == "{id=7,address={zip=10}}", "recursive print failed");
        std::cout << output.str() << '\n';
        std::cout << "OK 24-recursive-print\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
