// C++23 — std::mdspan, extents, layout_left и layout_right.
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
#include <mdspan>

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::array data{0, 1, 2, 3, 4, 5};
        using Shape = std::extents<std::size_t, 2, 3>;
        std::mdspan<int, Shape> rows(data.data());
        std::mdspan<int, Shape, std::layout_left> columns(data.data());
        check(rows[1, 0] == 3 && columns[1, 0] == 1, "layout mapping");
        rows[1, 2] = 7;
        check(data[5] == 7 && rows.rank() == 2 && rows.size() == 6, "shared storage");
        std::cout << rows[1, 2] << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
