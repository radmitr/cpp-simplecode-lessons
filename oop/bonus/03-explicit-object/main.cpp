// C++23 — явный параметр объекта; C++14 — decltype(auto).
#include <exception>
#include <iostream>
#include <type_traits>
#include <utility>

#include "../../../basics/bonus/common/check.hpp"

struct Box
{
    int value;
    template<class Self>
    decltype(auto) get(this Self&& self) { return (std::forward<Self>(self).value); }
};

int main()
{
    try
    {
        Box box{7};
        const Box constant{3};
        static_assert(std::is_same_v<decltype(box.get()), int&>);
        static_assert(std::is_same_v<decltype(constant.get()), const int&>);
        static_assert(std::is_same_v<decltype(Box{1}.get()), int&&>);
        box.get() = 9;
        check(box.value == 9, "reference accessor");
        std::cout << box.get() << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
