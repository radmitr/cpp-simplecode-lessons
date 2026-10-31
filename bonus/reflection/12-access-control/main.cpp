#include "../common/reflection.hpp"

class Vault { public: int visible = 1; private: int secret = 2; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        constexpr auto members = std::define_static_array(std::meta::nonstatic_data_members_of(
            ^^Vault, std::meta::access_context::unchecked()));
        static_assert(members.size() == 2);
        static_assert(std::meta::is_accessible(members[0], std::meta::access_context::unprivileged()));
        static_assert(!std::meta::is_accessible(members[1], std::meta::access_context::unprivileged()));
        Vault object;
        check(object.[:members[1]:] == 2, "unchecked reflection splice failed");
        std::cout << "unprivileged accessibility checked; unchecked splice reads private field\n";
        std::cout << "OK 12-access-control\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
