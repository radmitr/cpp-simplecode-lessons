// C++17 — распространение pmr-аллокатора на вложенные pmr::string.
#include <exception>
#include <iostream>
#include <memory_resource>
#include <string>
#include <vector>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::pmr::monotonic_buffer_resource arena;
        {
            std::pmr::vector<std::pmr::string> names(&arena);
            names.emplace_back(80, 'a');
            check(names[0].get_allocator().resource() == &arena, "nested PMR uses same resource");
            std::pmr::vector<std::string> ordinary(&arena);
            ordinary.emplace_back(80, 'b');
            check(names[0].size() == 80 && ordinary[0].size() == 80, "both strings contain data");
            std::cout << names[0].size() << ' ' << ordinary[0].size() << '\n';
        }
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
