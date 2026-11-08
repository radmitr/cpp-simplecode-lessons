// C++26 — вычисляемое сообщение static_assert и причина = delete.
#include <exception>
#include <iostream>
#include <string_view>

#include "../../../basics/additions/common/check.hpp"

constexpr std::string_view diagnostic = "int must hold at least 16 bits";
static_assert(sizeof(int) >= 2, diagnostic);
void open(int) = delete("pass a filename, not a numeric descriptor");
void open(std::string_view name) { std::cout << name << '\n'; }

int main()
{
    try
    {
        open("report.txt");
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
