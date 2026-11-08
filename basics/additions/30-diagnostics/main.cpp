// C++98 — границы массивов и время жизни объектов; C++11 — std::array; C++17 — [[maybe_unused]].
#include <array>
#include <cassert>
#include <cstddef>
#include <exception>
#include <iostream>

#include "../common/check.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(sizeof(char) == 1);
        const std::array<int, 3> data{1, 2, 3};
        const std::size_t index = 2;
        check(index < data.size(), "index out of bounds");
        assert(data[index] == 3);
        check(data.at(index) == 3, "checked access failed");
        std::cout << "compile-time, debug-only and always-active checks\n";
        std::cout << "OK 30-diagnostics\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
