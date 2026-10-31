#include <typeinfo>
#include "../common/check.hpp"

struct Base { virtual ~Base() = default; };
struct Derived : Base {};
struct Other : Base {};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        Derived object;
        Other other;
        Base* pointer = &object;
        check(dynamic_cast<Derived*>(pointer) == &object, "downcast failed");
        Base* otherPointer = &other;
        check(dynamic_cast<Derived*>(otherPointer) == nullptr, "wrong cast must be null");
        bool caught = false;
        try { (void)dynamic_cast<Derived&>(static_cast<Base&>(other)); }
        catch (const std::bad_cast&) { caught = true; }
        check(caught, "reference cast must throw");
        std::cout << "pointer failure: nullptr; reference failure: bad_cast\n";
        std::cout << "OK 03-dynamic-cast\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
