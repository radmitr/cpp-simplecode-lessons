// C++20 — корутины, co_yield и владение coroutine_handle.
#include <exception>
#include <iostream>
#include <stdexcept>
#include <utility>

#include "../../../basics/additions/common/check.hpp"
#include "sequence.hpp"

Sequence numbers() { co_yield 10; co_yield 20; }

int main()
{
    try
    {
        auto sequence = numbers();
        bool rejected = false;
        try { (void)sequence.value(); } catch (const std::logic_error&) { rejected = true; }
        check(rejected, "no value before first resume");
        check(sequence.next() && sequence.value() == 10, "first yield");
        auto owner = std::move(sequence);
        check(!sequence.next() && owner.next() && owner.value() == 20, "move owner");
        auto assigned = numbers();
        assigned = std::move(owner);
        check(!owner.next() && !assigned.next() && !assigned.next(), "assignment and completion");
        std::cout << "10 20\n";
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
