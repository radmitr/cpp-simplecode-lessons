#include <utility>
#include "../common/check.hpp"

template<class... T> constexpr auto sum(T... values) { return (0 + ... + values); }
template<class... T> constexpr bool all_positive(T... values) { return ((values > 0) && ...); }
template<class... F> void call_all(F&&... functions) { (std::forward<F>(functions)(), ...); }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(sum() == 0 && sum(1, 2, 3) == 6);
        static_assert(all_positive(1, 2, 3) && !all_positive(1, -2));
        int count = 0;
        call_all([&] { count += 1; }, [&] { count += 2; });
        check(count == 3, "call fold failed");
        std::cout << sum(1, 2, 3) << '\n';
        std::cout << "OK 19-parameter-packs\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
