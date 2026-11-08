// C++23 — auto(x) и auto{x}; C++98 — std::string.
#include <exception>
#include <iostream>
#include <string>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        std::string text = "old";
        const auto& reference = text;
        auto copy1 = auto(reference);
        auto copy2 = auto{reference};
        text = "new";
        check(copy1 == "old" && copy2 == "old", "independent copies");
        std::cout << copy1 << ' ' << copy2 << ' ' << text << '\n';
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
