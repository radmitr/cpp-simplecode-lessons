// C++23 — chunk, slide, stride, adjacent, chunk_by, join_with, repeat и cartesian_product.
#include <exception>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::vector values{1, 2, 3, 4, 5};
        check(std::ranges::distance(values | std::views::chunk(2)) == 3, "chunk groups");
        check(std::ranges::distance(values | std::views::slide(2)) == 4, "sliding windows");
        auto odd = values | std::views::stride(2) | std::ranges::to<std::vector>();
        check(odd == std::vector{1, 3, 5}, "stride");
        int adjacent_sum = 0;
        for (auto [a, b] : values | std::views::adjacent<2>) adjacent_sum += b - a;
        check(adjacent_sum == 4, "adjacent pairs");
        auto groups = values | std::views::chunk_by([](int a, int b) { return a / 3 == b / 3; });
        check(std::ranges::distance(groups) == 2, "neighbor grouping");
        std::vector words{std::string("red"), std::string("blue")};
        auto text = words | std::views::join_with('-') | std::ranges::to<std::string>();
        check(text == "red-blue", "join delimiter");
        auto product = std::views::cartesian_product(std::views::iota(0, 2), std::views::iota(0, 3));
        check(std::ranges::distance(product) == 6, "cartesian product");
        auto repeated = std::views::repeat(7) | std::views::take(3) | std::ranges::to<std::vector>();
        check(repeated == std::vector{7, 7, 7}, "bounded repeat");
        std::cout << text << ' ' << adjacent_sum << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
