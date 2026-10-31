#include <array>
#include <vector>
#include <type_traits>
#include <cstddef>
#include "../common/check.hpp"

template<class T, std::size_t N = 4> struct Buffer { std::array<T, N> values; };
template<class T> struct Pointer : std::false_type {};
template<class T> struct Pointer<T*> : std::true_type {};
template<class A, class B> struct Pair { A first; B second; };
template<class A, class B> Pair(A, B) -> Pair<A, B>;
template<class T> using Values = std::vector<T>;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Buffer<int, 3> buffer{};
        check(buffer.values.size() == 3, "non-type argument failed");
        static_assert(Pointer<int*>::value && !Pointer<int>::value);
        Pair pair{7, 2.5};
        static_assert(std::is_same_v<decltype(pair), Pair<int, double>>);
        Values<int> numbers{1, 2};
        check(numbers.size() == 2 && pair.first == 7, "alias or CTAD failed");
        std::cout << "type, value, partial specialization and deduction guide\n";
        std::cout << "OK 17-template-parameters\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
