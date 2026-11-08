// C++26 — std::linalg; C++23 — std::mdspan.
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
#include <mdspan>
#include <version>

#if __has_include(<linalg>)
#include <linalg>
#endif
#if defined(__cpp_lib_linalg)

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        std::array matrix_data{1.0, 2.0, 3.0, 4.0};
        std::array input_data{10.0, 20.0};
        std::array<double, 2> result_data{};
        std::mdspan<double, std::extents<std::size_t, 2, 2>> matrix(matrix_data.data());
        std::mdspan<double, std::extents<std::size_t, 2>> input(input_data.data());
        std::mdspan<double, std::extents<std::size_t, 2>> result(result_data.data());
        std::linalg::matrix_vector_product(matrix, input, result);
        const double squared = std::linalg::dot(input, input);
        check(result[0] == 50 && result[1] == 110 && squared == 500, "linear algebra");
        std::cout << result[0] << ' ' << result[1] << ' ' << squared << '\n';
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
    std::cout << "UNAVAILABLE: stl/bonus/24-linalg\n";
    return 77;
}
#endif
