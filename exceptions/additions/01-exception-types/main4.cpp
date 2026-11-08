// C++98 — std::bad_alloc, std::bad_cast и std::bad_typeid.
// C++11 — std::bad_weak_ptr и std::regex_error.
#include <exception>
#include <iostream>
#include <memory>
#include <new>
#include <regex>
#include <typeinfo>

#include "../../../basics/additions/common/check.hpp"

struct Base { virtual ~Base() = default; };
struct Derived : Base {};

int main()
{
    try
    {
        int caught = 0;
        try { throw std::bad_alloc(); } // Безопасная имитация, не исчерпываем память.
        catch (const std::bad_alloc&) { ++caught; std::cout << "bad_alloc: simulated\n"; }
        Base base;
        try { (void)dynamic_cast<Derived&>(base); }
        catch (const std::bad_cast&) { ++caught; std::cout << "bad_cast\n"; }
        Base* absent = nullptr;
        try { (void)typeid(*absent); } // Особое правило typeid для полиморфного типа.
        catch (const std::bad_typeid&) { ++caught; std::cout << "bad_typeid\n"; }
        try
        {
            std::weak_ptr<int> empty;
            std::shared_ptr<int> owner(empty);
        }
        catch (const std::bad_weak_ptr&) { ++caught; std::cout << "bad_weak_ptr\n"; }
        try { std::regex invalid("("); }
        catch (const std::regex_error&) { ++caught; std::cout << "regex_error\n"; }
        check(caught == 5, "missing exceptional case");
        std::cout << "OK rare-exceptions\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
