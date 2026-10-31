#include "../common/reflection.hpp"

class Vault
{
    int secret_ = 42;
public:
    int read() const
    {
        constexpr auto member = ^^Vault::secret_;
        static_assert(std::meta::is_accessible(member, std::meta::access_context::current()));
        return this->[:member:];
    }
};

int main()
{
    check(Vault{}.read() == 42, "member context lost access");
    std::cout << "OK member-access-context\n";
}
