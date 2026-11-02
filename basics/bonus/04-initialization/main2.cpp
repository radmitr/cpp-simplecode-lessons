// C++98 — инициализация через круглые скобки.
// C++11 — списковая инициализация и std::initializer_list.
#include <initializer_list>
#include <type_traits>
#include "../common/check.hpp"

int sum(std::initializer_list<int> values)
{
    int result = 0;
    for (int value : values)
        result += value;
    return result;
}

struct Object { int value = 7; };

int main()
{
    try
    {
        Object instance{}; // Объект.
        Object function(); // Объявление функции, возвращающей Object; тела нет.
        static_assert(std::is_function<decltype(function)>::value, "this is a function");
        check(instance.value == 7 && sum({1, 2, 3}) == 6 && sum({}) == 0,
              "initialization or list failed");
        std::cout << "Object: " << instance.value << "; list sum: " << sum({1, 2, 3}) << '\n';
        std::cout << "OK initializer-list\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
