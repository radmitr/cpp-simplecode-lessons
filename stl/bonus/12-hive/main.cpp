// C++26 — std::hive (зависит от реализации библиотеки).
#include <exception>
#include <iostream>
#include <memory>
#include <version>

#if __has_include(<hive>)
#include <hive>
#endif
#if defined(__cpp_lib_hive)

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::hive<int> values;
        auto first = values.insert(7);
        int* address = std::addressof(*first);
        auto removed = values.insert(3);
        values.erase(removed);
        values.insert(9);
        check(std::addressof(*first) == address && *first == 7, "stable live address");
        values.insert(7);
        values.sort();
        values.unique();
        check(values.size() == 2 && *values.begin() == 7, "sort and unique");
        for (int value : values) std::cout << value << ' ' ;
        std::cout << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
#else
int main()
{
    std::cout << "UNAVAILABLE: stl/bonus/12-hive\n";
    return 77;
}
#endif
