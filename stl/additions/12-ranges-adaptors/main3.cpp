// C++23 — ranges::fold_left/fold_right/find_last/contains и views::as_rvalue/as_const.
#include <algorithm>
#include <exception>
#include <functional>
#include <iostream>
#include <memory>
#include <ranges>
#include <type_traits>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::vector values{1, 2, 3, 2};
        check(std::ranges::fold_left(values, 0, std::plus{}) == 8, "left fold");
        check(std::ranges::fold_right(values, 0, std::minus{}) == 0, "right fold");
        auto found = std::ranges::find_last(values, 2);
        check(!found.empty() && std::ranges::distance(found) == 1, "last occurrence");
        check(std::ranges::contains(values, 3) && std::ranges::find_last(values, 9).empty(), "search");
        auto constant = values | std::views::as_const;
        static_assert(std::is_const_v<std::remove_reference_t<decltype(*constant.begin())>>);
        std::vector<std::unique_ptr<int>> owners;
        owners.push_back(std::make_unique<int>(7));
        auto moved = owners | std::views::as_rvalue | std::ranges::to<std::vector>();
        check(!owners[0] && *moved[0] == 7, "moving from a view");
        std::cout << 8 << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
