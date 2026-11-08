// C++20 — co_return, operator co_await и передача продолжения.
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string_view>
#include <utility>

#include "../../../basics/additions/common/check.hpp"
#include "../common/task.hpp"

Task<int> child(bool fail)
{
    if (fail) throw std::runtime_error("child failed");
    co_return 21;
}
Task<int> parent(bool fail)
{
    const int value = co_await child(fail);
    co_return value * 2;
}
int main()
{
    try
    {
        auto good = parent(false);
        bool premature = false;
        try { good.result(); }
        catch (const std::logic_error&) { premature = true; }
        check(premature, "result requires completion");
        good.resume();
        check(good.done() && good.result() == 42, "nested result");
        auto bad = parent(true);
        bad.resume();
        bool caught = false;
        try { bad.result(); }
        catch (const std::runtime_error& e) { caught = std::string_view(e.what()) == "child failed"; }
        check(caught, "exception propagated through await_resume");
        std::cout << "42; child failed\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
