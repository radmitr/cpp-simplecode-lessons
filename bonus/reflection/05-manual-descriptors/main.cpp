#include <array>
#include <string_view>
#include "../common/check.hpp"

struct Person { int id; int age; };
struct Field { std::string_view name; int Person::*member; };
constexpr std::array<Field, 2> fields{{{"id", &Person::id}, {"age", &Person::age}}};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Person person{10, 20};
        for (const auto& field : fields)
        {
            person.*field.member += 1;
            std::cout << field.name << '=' << person.*field.member << '\n';
        }
        check(person.id == 11 && person.age == 21, "descriptor update failed");
        std::cout << "OK 05-manual-descriptors\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
