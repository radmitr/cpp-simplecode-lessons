// C++17 — merge узлов ассоциативных контейнеров.
#include <exception>
#include <iostream>
#include <map>
#include <set>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::map<int, int> target{{1, 10}};
        std::map<int, int> source{{1, 11}, {2, 20}};
        target.merge(source);
        check(target.size() == 2 && source.size() == 1, "duplicate remains in source");
        check(target.at(1) == 10 && source.at(1) == 11 && target.at(2) == 20, "no overwrite");
        std::set<int> unique{1};
        std::multiset<int> repeated{1, 2, 2};
        unique.merge(repeated);
        check(unique.size() == 2 && repeated.size() == 2, "compatible set nodes");
        std::cout << target.at(1) << ' ' << target.at(2) << ' ' << source.at(1) << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
