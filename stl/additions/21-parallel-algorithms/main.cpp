// C++17 — политики seq/par/par_unseq и параллельные алгоритмы.
#include <algorithm>
#include <exception>
#include <execution>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::vector<int> values(100);
        std::iota(values.begin(), values.end(), 1);
        const auto sequential = std::accumulate(values.begin(), values.end(), 0LL);
        const auto reduced = std::reduce(std::execution::par, values.begin(), values.end(), 0LL);
        check(sequential == 5050 && reduced == sequential, "associative bounded integer reduction");
        std::vector<int> doubled(values.size());
        std::transform(std::execution::par_unseq, values.begin(), values.end(), doubled.begin(),
            [](int x) noexcept { return 2 * x; });
        std::sort(std::execution::par, doubled.begin(), doubled.end(), std::greater<int>{});
        check(doubled.front() == 200 && doubled.back() == 2, "parallel transform and sort");
        std::cout << reduced << ' ' << doubled.front() << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
