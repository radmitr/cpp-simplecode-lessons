#include <string_view>
#include "../common/check.hpp"

template<class T> T larger(T a, T b) { return a < b ? b : a; }
std::string_view kind(int) { return "ordinary"; }
template<class T> std::string_view kind(T) { return "template"; }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        check(larger(2, 5) == 5, "int deduction failed");
        check(larger(2.5, 1.0) == 2.5, "double deduction failed");
        check(larger<double>(2, 2.5) == 2.5, "explicit argument failed");
        check(kind(1) == "ordinary" && kind(1.5) == "template", "overload choice failed");
        // larger(2, 2.5); // Нельзя вывести один T из разных типов аргументов.
        std::cout << larger<double>(2, 2.5) << '\n';
        std::cout << "OK 16-function-templates\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
