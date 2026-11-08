// C++20 — очистка кадра корутины и unhandled_exception.
#include <exception>
#include <iostream>
#include <stdexcept>

#include "../../../basics/additions/common/check.hpp"
#include "sequence.hpp"

struct Guard
{
    inline static int alive = 0;
    Guard() { ++alive; }
    ~Guard() { --alive; }
};
Sequence failing()
{
    Guard guard;
    co_yield 1;
    throw std::runtime_error("coroutine failure");
}

int main()
{
    try
    {
        {
            auto sequence = failing();
            check(Guard::alive == 0, "lazy start");
            check(sequence.next() && Guard::alive == 1, "suspended local lifetime");
        }
        check(Guard::alive == 0, "early destroy");
        auto sequence = failing();
        check(sequence.next(), "first value");
        bool caught = false;
        try { (void)sequence.next(); } catch (const std::runtime_error&) { caught = true; }
        check(caught && Guard::alive == 0, "exception propagation and unwinding");
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
