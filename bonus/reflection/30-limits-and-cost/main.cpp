#include "../common/reflection.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        struct Local { int id; };
        Local object{7};
        int visited = 0;
        reflection_demo::for_each_field(object, [&](auto, const auto&) { ++visited; });
        check(visited == 1, "expected one generated field operation");
        std::cout << "metadata at compile time; values at runtime\n";
        std::cout << "names are not a stable schema; no arbitrary runtime type loading\n";
        std::cout << "OK 30-limits-and-cost\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
