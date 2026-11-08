// C++23 — dextents и layout_stride.
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
#include <mdspan>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::array<int, 8> data{};
        using Shape = std::dextents<std::size_t, 2>;
        const Shape shape(2, 3);
        std::layout_stride::mapping<Shape> mapping(shape, std::array<std::size_t, 2>{4, 1});
        std::mdspan<int, Shape, std::layout_stride> matrix(data.data(), mapping);
        matrix[1, 2] = 9;
        check(data[6] == 9 && data[3] == 0, "strided mapping");
        check(matrix.extent(0) == 2 && matrix.extent(1) == 3 && mapping.required_span_size() == 7, "sizes");
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
