// C++17 — optional; прикладная модель — least-connections и health state.
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
#include <optional>

#include "../../../basics/additions/common/check.hpp"

struct Backend { bool healthy; unsigned active; };
std::optional<std::size_t> choose(const std::array<Backend, 3>& backends)
{
    std::optional<std::size_t> selected;
    for (std::size_t i = 0; i < backends.size(); ++i)
        if (backends[i].healthy && (!selected || backends[i].active < backends[*selected].active)) selected = i;
    return selected;
}
int main()
{
    try
    {
        std::array backends{Backend{true, 3}, Backend{false, 0}, Backend{true, 1}};
        auto selected = choose(backends);
        check(selected && *selected == 2, "least active healthy backend");
        ++backends[*selected].active;
        backends[2].healthy = false;
        selected = choose(backends);
        check(selected && *selected == 0, "exclude failed backend");
        backends[0].healthy = false;
        check(!choose(backends), "no healthy backend");
        backends[1].healthy = true;
        check(choose(backends) == 1, "recovered backend");
        std::cout << "2 -> 0 -> unavailable -> 1\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
