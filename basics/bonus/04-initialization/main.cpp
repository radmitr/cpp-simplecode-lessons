#include <vector>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        int zero{};
        std::vector<int> sizeAndValue(3, 7);
        std::vector<int> elements{3, 7};
        check(zero == 0 && sizeAndValue.size() == 3 && elements.size() == 2, "initialization choice failed");
        check(sizeAndValue[0] == 7 && elements[0] == 3, "wrong constructor selected");
        const double number = 3.5;
        const int explicitConversion = static_cast<int>(number);
        // int narrowing{number}; // Ошибка: сужающее преобразование.
        check(explicitConversion == 3, "integer conversion failed");
        std::cout << "(3,7): " << sizeAndValue.size() << "; {3,7}: " << elements.size() << '\n';
        std::cout << "OK 04-initialization\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
