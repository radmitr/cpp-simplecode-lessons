// C++26 — std::inplace_vector.
#include <exception>
#include <iostream>
#include <new>
#include <version>

#if __has_include(<inplace_vector>)
#include <inplace_vector>
#endif
#if defined(__cpp_lib_inplace_vector)

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::inplace_vector<int, 3> values;
        values.push_back(1);
        check(bool(values.try_push_back(2)), "try insert");
        if (values.size() < values.capacity()) values.unchecked_push_back(3);
        check(!values.try_push_back(4) && values.size() == 3, "full capacity");
        bool full = false;
        try { values.push_back(4); } catch (const std::bad_alloc&) { full = true; }
        check(full, "overflow exception");
        std::inplace_vector<int, 0> empty;
        check(empty.empty() && !empty.try_push_back(1), "zero capacity");
        values.pop_back();
        check(values.size() == 2 && values.capacity() == 3, "size and capacity");
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
    std::cout << "UNAVAILABLE: stl/additions/16-inplace-vector\n";
    return 77;
}
#endif
