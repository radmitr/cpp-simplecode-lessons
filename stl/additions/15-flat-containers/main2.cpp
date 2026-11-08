// C++23 — std::flat_set, flat_multiset и sorted_unique.
#include <exception>
#include <flat_set>
#include <iostream>
#include <vector>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::flat_set<int> values{3, 1, 3, 2};
        check(values.size() == 3 && *values.begin() == 1, "ordered unique keys");
        check(!values.insert(2).second && values.contains(3), "set insertion");
        values.erase(1);
        std::flat_multiset<int> duplicates{1, 1, 2};
        check(duplicates.count(1) == 2, "duplicate keys");
        std::flat_set<int> ordered(std::sorted_unique, std::vector{2, 4, 6});
        check(ordered.size() == 3 && ordered.contains(4), "trusted sorted input");
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
