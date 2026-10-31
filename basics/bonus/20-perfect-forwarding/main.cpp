#include <string>
#include <string_view>
#include <utility>
#include "../common/check.hpp"

std::string_view select(const std::string&) { return "lvalue"; }
std::string_view select(std::string&&) { return "rvalue"; }
template<class T> std::string_view route(T&& value) { return select(std::forward<T>(value)); }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        std::string text = "Ada";
        check(route(text) == "lvalue", "lvalue lost");
        check(route(std::string("temporary")) == "rvalue", "rvalue lost");
        check(route(std::move(text)) == "rvalue", "move category lost");
        check(text == "Ada", "category test should not move data");
        std::cout << "forward preserved value category\n";
        std::cout << "OK 20-perfect-forwarding\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
