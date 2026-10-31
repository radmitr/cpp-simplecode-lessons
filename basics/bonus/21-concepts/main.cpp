#include <concepts>
#include <vector>
#include "../common/check.hpp"

struct NoAdd {};
template<class T> concept Addable = requires(T a, T b) { { a + b } -> std::same_as<T>; };
template<Addable T> T add(T a, T b) { return a + b; }
template<class T> requires requires(const T& value) { value.size(); }
auto count(const T& value) { return value.size(); }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(Addable<int>);
        static_assert(!Addable<NoAdd>);
        check(add(2, 3) == 5, "constrained add failed");
        std::vector<int> values{1, 2};
        check(count(values) == 2, "requires expression failed");
        std::cout << "constraints checked before instantiation\n";
        std::cout << "OK 21-concepts\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
