#include <array>
#include <iostream>

// constexpr разрешает вычисление при компиляции, но не требует его для каждого вызова.
constexpr int square(int value)
{
    return value * value;
}

// consteval требует, чтобы каждый обычный вызов был константным выражением.
consteval int compileTimeSquare(int value)
{
    return value * value;
}

constexpr int count = square(3);
static_assert(count == 9, "Unexpected array size");
static_assert(compileTimeSquare(5) == 25);

int main()
{
    std::array<int, count> values{};
    // Сама переменная может быть изменяемой: consteval относится к вызову функции.
    int result = compileTimeSquare(5);
    ++result;

    std::cout << "constexpr square: " << count << '\n';
    std::cout << "array size: " << values.size() << '\n';
    std::cout << "consteval result after increment: " << result << '\n';
}
