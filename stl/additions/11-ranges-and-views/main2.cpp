// C++20 — ref_view, owning_view и borrowed_range.
#include <exception>
#include <iostream>
#include <ranges>
#include <span>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::vector numbers{1, 2};
        auto reference = std::views::all(numbers);
        numbers[0] = 9;
        check(*reference.begin() == 9, "reference view");
        auto owner = std::views::all(std::vector{3, 4});
        check(*owner.begin() == 3, "owning view");
        static_assert(std::ranges::borrowed_range<std::span<int>>);
        static_assert(!std::ranges::borrowed_range<std::vector<int>>);
        std::cout << *reference.begin() << ' ' << *owner.begin() << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
