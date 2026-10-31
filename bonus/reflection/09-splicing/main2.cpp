#include "../common/reflection.hpp"

int shared_value = 7;
int increment(int value) { return value + 1; }

int main()
{
    constexpr auto object = std::meta::reflect_object(shared_value);
    constexpr auto function = std::meta::reflect_function(increment);
    constexpr auto constant = std::meta::reflect_constant(42);
    constexpr int answer = std::meta::extract<int>(constant);
    constexpr auto address = std::meta::reflect_constant(&shared_value);
    constexpr int* pointer = std::meta::extract<int*>(address);
    [:object:] = 9;
    check(pointer == &shared_value && *pointer == 9, "object reflection failed");
    check([:function:](answer) == 43, "function reflection failed");
    std::cout << "OK object-function-extraction\n";
}
