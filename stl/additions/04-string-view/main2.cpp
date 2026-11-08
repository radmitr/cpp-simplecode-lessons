// C++17 — string_view: подстрока, проверка границ и явное владение.
#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

#include "../../../basics/additions/common/check.hpp"

int main()
{
    try
    {
        const std::string owner = "abcdef";
        const std::string_view prefix(owner.data(), 3);
        check(prefix == "abc" && prefix.data()[3] == 'd', "no terminator at view boundary");
        const std::string terminated(prefix);
        check(terminated.c_str()[3] == '\0', "explicit owning C string");
        check(prefix.substr(1) == "bc", "subview");
        bool caught = false;
        try { (void)prefix.at(3); }
        catch (const std::out_of_range&) { caught = true; }
        check(caught && prefix.find('z') == std::string_view::npos, "bounds and missing match");
        std::cout << prefix << ' ' << terminated << '\n';
        std::cout << "OK reference-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
