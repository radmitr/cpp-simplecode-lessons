// C++26 — время жизни элементов std::inplace_vector.
#include <exception>
#include <iostream>
#include <version>

#if __has_include(<inplace_vector>)
#include <inplace_vector>
#endif
#if defined(__cpp_lib_inplace_vector)

#include "../../../basics/bonus/common/check.hpp"

struct Tracked
{
    inline static int alive = 0;
    Tracked() { ++alive; }
    Tracked(const Tracked&) { ++alive; }
    ~Tracked() { --alive; }
};

int main()
{
    try
    {
        {
            std::inplace_vector<Tracked, 8> values;
            check(Tracked::alive == 0, "no eager construction");
            values.emplace_back();
            values.emplace_back();
            check(Tracked::alive == 2, "live elements");
            values.pop_back();
            check(Tracked::alive == 1, "destruction on removal");
        }
        check(Tracked::alive == 0, "container cleanup");
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
    std::cout << "UNAVAILABLE: stl/bonus/16-inplace-vector\n";
    return 77;
}
#endif
