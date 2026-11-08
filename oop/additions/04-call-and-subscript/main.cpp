// C++23 — многомерный operator[], static operator() и static operator[].
#include <array>
#include <cstddef>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "../../../basics/additions/common/check.hpp"

struct Matrix
{
    std::array<int, 6> cells{};
    int& operator[](std::size_t row, std::size_t column)
    {
        if (row >= 2 || column >= 3) throw std::out_of_range("matrix index");
        return cells[row * 3 + column];
    }
    const int& operator[](std::size_t row, std::size_t column) const
    {
        if (row >= 2 || column >= 3) throw std::out_of_range("matrix index");
        return cells[row * 3 + column];
    }
};
struct Twice
{
    static int operator()(int x) { return x * 2; }
    static int operator[](int x) { return x * 2; }
};

int main()
{
    try
    {
        Matrix matrix;
        matrix[1, 2] = 7;
        const Matrix& view = matrix;
        check(view[1, 2] == 7, "const subscript");
        check(matrix[1, 2] == 7 && Twice{}(3) == 6 && Twice{}[3] == 6, "operators");
        const auto triple = [](int x) static { return x * 3; };
        check(triple(2) == 6, "static lambda");
        bool rejected = false;
        try { (void)matrix[2, 0]; } catch (const std::out_of_range&) { rejected = true; }
        check(rejected, "bounds");
        std::cout << matrix[1, 2] << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
