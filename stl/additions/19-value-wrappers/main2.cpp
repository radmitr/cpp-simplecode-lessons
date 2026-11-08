// C++26 — std::polymorphic; C++98 — виртуальные функции.
#include <exception>
#include <iostream>
#include <memory>
#include <utility>
#include <version>

#if defined(__cpp_lib_polymorphic)

#include "../../../basics/additions/common/check.hpp"

struct Shape { virtual ~Shape() = default; virtual int size() const = 0; };
struct Circle : Shape
{
    int radius;
    explicit Circle(int r) : radius(r) {}
    int size() const override { return radius; }
};

int main()
{
    try
    {
        std::polymorphic<Shape> original(std::in_place_type<Circle>, 3);
        auto copy = original;
        check(original->size() == 3 && copy->size() == 3 && &*original != &*copy, "polymorphic copy");
        std::cout << copy->size() << '\n';
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
    std::cout << "UNAVAILABLE: stl/additions/19-value-wrappers\n";
    return 77;
}
#endif
