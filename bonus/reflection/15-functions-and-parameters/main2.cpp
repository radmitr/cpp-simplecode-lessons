#include "../common/reflection.hpp"

int operation(int value) { return value + 1; }
double operation(double value) { return value + 0.5; }

int main()
{
    constexpr auto selected = static_cast<int(*)(int)>(&operation);
    constexpr auto function = std::meta::reflect_function(*selected);
    static_assert(std::meta::return_type_of(function) == ^^int);
    check([:function:](3) == 4, "selected overload failed");
    std::cout << "OK reflected-overload\n";
}
