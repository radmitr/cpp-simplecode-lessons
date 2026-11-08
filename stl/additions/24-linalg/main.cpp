// C++26 — std::linalg; C++23 — std::mdspan; внешний профиль — Kokkos stdBLAS.
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
#include <mdspan>
#include <version>

#if defined(CPP_USE_STDBLAS)
// mdspan задаёт namespace до включения заголовков stdBLAS.
#include <mdspan/mdspan.hpp>
#include <experimental/linalg>
namespace md_demo = Kokkos;
namespace linalg_demo = Kokkos::Experimental::linalg;
#elif __has_include(<linalg>)
#include <linalg>
namespace md_demo = std;
namespace linalg_demo = std::linalg;
#endif
#if defined(CPP_USE_STDBLAS) || defined(__cpp_lib_linalg)

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::array matrix_data{1.0, 2.0, 3.0, 4.0};
        std::array input_data{10.0, 20.0};
        std::array<double, 2> result_data{};
        md_demo::mdspan<double, md_demo::extents<std::size_t, 2, 2>> matrix(matrix_data.data());
        md_demo::mdspan<double, md_demo::extents<std::size_t, 2>> input(input_data.data());
        md_demo::mdspan<double, md_demo::extents<std::size_t, 2>> result(result_data.data());
        linalg_demo::matrix_vector_product(matrix, input, result);
        const double squared = linalg_demo::dot(input, input);
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
    std::cout << "UNAVAILABLE: stl/additions/24-linalg\n";
    return 77;
}
#endif
