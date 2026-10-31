#include <iostream>

constexpr int square(int value)
{
    return value * value;
}

consteval int compileTimeSquare(int value)
{
    return value * value;
}

int main()
{
    std::cout << "Enter an integer from -100 to 100: ";
    int value = 0;
    if (!(std::cin >> value) || value < -100 || value > 100)
    {
        std::cerr << "Invalid input\n";
        return 1;
    }

    const int result = square(value);
    std::cout << "runtime square: " << result << '\n';

    // const запрещает менять result, но не превращает ввод в константное выражение.
    // constexpr int invalid = square(value); // Ошибка: value известен только при запуске.
    // int alsoInvalid = compileTimeSquare(value); // Ошибка по той же причине.
    // static_assert(result == 25); // Для проверки при запуске нужен обычный if.
}
