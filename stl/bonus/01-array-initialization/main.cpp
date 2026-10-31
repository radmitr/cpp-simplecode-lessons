#include <array>
#include <iostream>

int main()
{
    std::array<int, 5> a{}; // Все элементы равны нулю.
    a.at(0) = 42;          // Проверяемый доступ.
    auto copy = a;        // Самостоятельные элементы, а не ссылка.
    copy.at(0) = 7;

    std::array<int, 0> empty{};
    // У пустого массива нельзя вызывать front()/back() или разыменовывать begin().
    std::cout << "Original: " << a.at(0) << ", last=" << a.back() << '\n';
    std::cout << "Copy: " << copy.at(0) << '\n';
    std::cout << "Empty: " << std::boolalpha << empty.empty()
              << ", begin equals end: " << (empty.begin() == empty.end()) << '\n';
    return a.at(0) == 42 && a.back() == 0 && copy.at(0) == 7 &&
                   empty.empty() && empty.begin() == empty.end() ? 0 : 1;
}
