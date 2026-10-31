#include "../common/reflection.hpp"

struct Record { int id; std::string name; inline static int count = 0; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(std::meta::nonstatic_data_members_of(^^Record, std::meta::access_context::unprivileged()).size() == 2);
        static_assert(std::meta::static_data_members_of(^^Record, std::meta::access_context::unprivileged()).size() == 1);
        Record record{7, "Ada"};
        reflection_demo::for_each_field(record, [](auto name, const auto& value) {
            std::cout << name << '=' << value << '\n';
        });
        std::cout << "OK 11-data-members\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
