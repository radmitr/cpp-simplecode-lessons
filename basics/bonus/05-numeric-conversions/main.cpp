#include <limits>
#include <cstddef>
#include "../common/check.hpp"

bool can_add_one(int value) { return value < std::numeric_limits<int>::max(); }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        const int negative = -1;
        const std::size_t length = 3;
        check(negative < 0, "negative test failed");
        // Сначала проверяем знак, затем выполняем беззнаковое преобразование.
        check(!(negative >= 0 && static_cast<std::size_t>(negative) < length), "bad index accepted");
        const auto maximum = std::numeric_limits<int>::max();
        check(!can_add_one(maximum) && can_add_one(5), "overflow guard failed");
        check(5 / 2 == 2 && 5.0 / 2 == 2.5, "division failed");
        check(0.1 + 0.2 != 0.3, "expected floating point demonstration");
        std::cout << "int digits=" << std::numeric_limits<int>::digits << '\n';
        std::cout << "OK 05-numeric-conversions\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
