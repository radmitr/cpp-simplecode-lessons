// C++20 — std::ranges и представления filter/transform/take.
#include <algorithm>
#include <exception>
#include <iostream>
#include <iterator>
#include <ranges>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::vector numbers{1, 2, 3, 4, 5, 6};
        auto view = numbers | std::views::filter([](int n) { return n % 2 == 0; })
            | std::views::transform([](int n) { return n * 10; }) | std::views::take(2);
        std::vector<int> result;
        std::ranges::copy(view, std::back_inserter(result));
        check(result == std::vector{20, 40}, "lazy pipeline");
        for (int n : result) std::cout << n << ' ' ;
        std::cout << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
