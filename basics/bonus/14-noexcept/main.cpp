#include <type_traits>
#include <utility>
#include <vector>
#include "../common/check.hpp"

struct Safe { Safe() = default; Safe(Safe&&) noexcept = default; ~Safe() noexcept = default; };
struct Risky { Risky() = default; Risky(const Risky&) = default; Risky(Risky&&) noexcept(false) {} };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(noexcept(std::declval<Safe&>().~Safe()));
        static_assert(std::is_nothrow_move_constructible_v<Safe>);
        static_assert(!std::is_nothrow_move_constructible_v<Risky>);
        Risky value;
        static_assert(std::is_same_v<decltype(std::move_if_noexcept(value)), const Risky&>);
        std::vector<Safe> values;
        values.emplace_back(); values.emplace_back();
        check(values.size() == 2, "vector construction failed");
        std::cout << "noexcept traits checked without triggering terminate\n";
        std::cout << "OK 14-noexcept\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
