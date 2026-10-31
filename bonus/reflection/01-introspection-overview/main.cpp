#include <type_traits>
#include "../common/check.hpp"

struct Record { int id; };
struct Descriptor { const char* name; int Record::*member; };
constexpr Descriptor descriptors[] = {{"id", &Record::id}};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Record record{7};
        std::cout << "manual field: " << descriptors[0].name << '='
                  << record.*descriptors[0].member << '\n';
        static_assert(std::is_standard_layout_v<Record>);
        check(record.*descriptors[0].member == 7, "manual descriptor failed");
        std::cout << "OK 01-introspection-overview\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
