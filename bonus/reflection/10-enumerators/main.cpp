#include "../common/reflection.hpp"

enum class State { ready = 1, alias = 1, stopped = 4 };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        template for (constexpr auto item : std::define_static_array(std::meta::enumerators_of(^^State)))
            std::cout << std::meta::identifier_of(item) << '=' << static_cast<int>([:item:]) << '\n';
        static_assert(std::meta::enumerators_of(^^State).size() == 3);
        check(reflection_demo::enum_name(State::alias) == "ready", "first matching name expected");
        check(reflection_demo::enum_name(static_cast<State>(99)).empty(), "unknown value must be handled");
        std::cout << "OK 10-enumerators\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
