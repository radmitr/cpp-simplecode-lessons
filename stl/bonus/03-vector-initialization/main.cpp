// C++98 — конструкторы std::vector; C++11 — конструктор со std::initializer_list.
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> a(20);     // 20 нулей: аргумент задаёт размер.
    std::vector<int> b{20};     // Один элемент со значением 20: список значений.
    std::vector<int> c(20, 55); // 20 элементов со значением 55.
    std::vector<int> d{20, 55}; // Два элемента: 20 и 55.

    std::cout << "a: size=" << a.size() << ", first=" << a.front() << '\n';
    std::cout << "b: size=" << b.size() << ", first=" << b.front() << '\n';
    std::cout << "c: size=" << c.size() << ", first=" << c.front() << '\n';
    std::cout << "d: size=" << d.size() << ", first=" << d.front()
              << ", last=" << d.back() << '\n';
    return a.size() == 20 && a.front() == 0 && b.size() == 1 && b.front() == 20 &&
                   c.size() == 20 && c.front() == 55 && d.size() == 2 &&
                   d.front() == 20 && d.back() == 55 ? 0 : 1;
}
