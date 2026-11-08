// C++20 — параметры в кадре корутины; C++14 — захват лямбды.
#include <exception>
#include <iostream>
#include <string>
#include <utility>

#include "../../../basics/additions/common/check.hpp"
#include "../common/task.hpp"

Task<int> owned(std::string text) { co_return static_cast<int>(text.size()); }
Task<int> borrowed(const std::string& text) { co_return static_cast<int>(text.size()); }
int main()
{
    try
    {
        auto first = owned(std::string("hello"));
        first.resume();
        check(first.result() == 5, "value parameter owns its string");
        std::string owner = "abc";
        auto second = borrowed(owner);
        owner += "d";
        second.resume();
        check(second.result() == 4, "reference observes live owner");
        auto closure = [text = std::string("capture")]() -> Task<int> {
            co_return static_cast<int>(text.size());
        };
        auto third = closure();
        third.resume();
        check(third.result() == 7, "closure stays alive");
        auto safer = [](std::string text) -> Task<int> { co_return static_cast<int>(text.size()); };
        auto fourth = safer("value");
        fourth.resume();
        check(fourth.result() == 5, "explicit value parameter");
        std::cout << "5 4 7 5\nOK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
