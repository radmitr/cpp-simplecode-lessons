// C++26 — пакеты и constexpr структурированных привязок.
#include <array>
#include <exception>
#include <iostream>
#include <utility>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::array values{1, 2, 3};
        const auto visit = []<class T>(T& source) {
            auto [first, ...tail] = source;
            const int sum = (0 + ... + tail);
            check(first == 1 && sum == 5, "binding pack");
            auto& [head, ...rest] = source;
            head = 9;
            check(source[0] == 9 && sizeof...(rest) == 2, "reference pack");
            std::cout << first << ' ' << sum << '\n';
        };
        visit(values);
        struct Pair { int x; int y; };
        constexpr auto [x, y] = Pair{2, 3};
        static_assert(x + y == 5);
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
