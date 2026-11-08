// C++23 — views::zip, views::enumerate и ranges::to.
#include <exception>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::vector names{std::string("Ada"), std::string("Lin")};
        std::vector scores{7, 9, 10};
        int total = 0;
        for (auto [name, score] : std::views::zip(names, scores))
        {
            total += score;
            std::cout << name << '=' << score << '\n';
        }
        check(total == 16, "shortest zip");
        for (auto [index, score] : scores | std::views::enumerate) score += static_cast<int>(index);
        auto copy = scores | std::views::take(2) | std::ranges::to<std::vector<int>>();
        check(copy == std::vector{7, 10}, "enumerate references and materialization");
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
