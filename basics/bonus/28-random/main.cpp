#include <random>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        std::mt19937 first(12345), second(12345);
        check(first() == second(), "equal seeds must reproduce engine sequence");
        std::uniform_int_distribution<int> die(1, 6);
        int total = 0;
        for (int i = 0; i < 100; ++i) {
            const int value = die(first);
            check(value >= 1 && value <= 6, "distribution outside range");
            total += value;
        }
        check(total >= 100 && total <= 600, "sum outside range");
        std::cout << "100 die rolls stay within bounds\n";
        std::cout << "OK 28-random\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
