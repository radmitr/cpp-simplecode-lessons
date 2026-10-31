#include "../common/reflection.hpp"

struct Record { int id; };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        constexpr auto type = ^^int;
        typename [:type:] number = 5;
        constexpr auto member = ^^Record::id;
        Record object{7};
        object.[:member:] += number;
        constexpr auto reflected = std::meta::reflect_constant(42);
        constexpr int answer = [:reflected:];
        check(object.id == 12 && answer == 42, "splice failed");
        std::cout << object.id << ' ' << answer << '\n';
        std::cout << "OK 09-splicing\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
