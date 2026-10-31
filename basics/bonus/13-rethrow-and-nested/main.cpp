#include <exception>
#include <stdexcept>
#include "../common/check.hpp"

struct Detail : std::runtime_error { int code = 7; Detail() : std::runtime_error("detail") {} };
void relay() { try { throw Detail{}; } catch (const std::exception&) { throw; } }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        bool preserved = false;
        try { relay(); }
        catch (const Detail& error) { preserved = error.code == 7; }
        check(preserved, "throw; must preserve dynamic exception type");
        bool nested = false;
        try {
            try { throw std::invalid_argument("bad field"); }
            catch (...) { std::throw_with_nested(std::runtime_error("configuration failed")); }
        } catch (const std::exception& outer) {
            try { std::rethrow_if_nested(outer); }
            catch (const std::invalid_argument&) { nested = true; }
        }
        check(nested, "nested context missing");
        std::cout << "dynamic type and nested cause preserved\n";
        std::cout << "OK 13-rethrow-and-nested\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
