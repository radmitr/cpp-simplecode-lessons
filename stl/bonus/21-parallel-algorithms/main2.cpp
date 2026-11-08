// C++17 — transform_reduce; C++20 — execution::unseq.
#include <algorithm>
#include <exception>
#include <execution>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        const std::vector<int> values{1, 2, 3, 4, 5};
        const int squares = std::transform_reduce(std::execution::seq, values.begin(), values.end(), 0,
            std::plus<int>{}, [](int x) noexcept { return x * x; });
        std::vector<int> output(values.size());
        std::transform(std::execution::unseq, values.begin(), values.end(), output.begin(),
            [](int x) noexcept { return x + 1; });
        check(squares == 55 && output == std::vector<int>({2, 3, 4, 5, 6}), "policy algorithms");
        std::cout << squares << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
