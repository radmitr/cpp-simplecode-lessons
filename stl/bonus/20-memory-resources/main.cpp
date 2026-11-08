// C++17 — pmr::vector, monotonic_buffer_resource и null_memory_resource.
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
#include <memory_resource>
#include <new>
#include <vector>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        alignas(std::max_align_t) std::array<std::byte, 256> storage{};
        std::pmr::monotonic_buffer_resource arena(storage.data(), storage.size(), std::pmr::null_memory_resource());
        {
            std::pmr::vector<int> values(&arena);
            values.reserve(4);
            values.push_back(7);
            values.push_back(9);
            bool exhausted = false;
            try { values.reserve(10000); }
            catch (const std::bad_alloc&) { exhausted = true; }
            check(exhausted && values.size() == 2 && values[0] == 7, "fixed arena exhaustion");
            std::cout << values[0] << ' ' << values[1] << '\n';
        }
        arena.release(); // Все пользователи арены уже уничтожены.
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
