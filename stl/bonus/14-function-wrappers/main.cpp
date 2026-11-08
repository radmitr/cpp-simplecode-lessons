// C++26 — std::function_ref и std::copyable_function.
#include <exception>
#include <functional>
#include <iostream>
#include <version>

#if defined(__cpp_lib_function_ref) && defined(__cpp_lib_copyable_function)

#include "../../../basics/bonus/common/check.hpp"

int main()
{
    try
    {
        int offset = 2;
        auto target = [&](int x) { return x + offset; };
        std::function_ref<int(int)> reference(target);
        check(reference(3) == 5, "borrowed callable");
        offset = 4;
        check(reference(3) == 7, "same target");
        std::copyable_function<int(int) const noexcept> owned = [](int x) noexcept { return x * 2; };
        auto copy = owned;
        check(owned && copy && copy(3) == 6, "copyable wrapper");
        static_assert(noexcept(copy(3)));
        std::cout << reference(3) << ' ' << copy(3) << '\n';
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
    std::cout << "UNAVAILABLE: stl/bonus/14-function-wrappers\n";
    return 77;
}
#endif
