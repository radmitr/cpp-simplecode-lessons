#include "../common/reflection.hpp"

consteval bool guarded_identifier_request()
{
    try { (void)std::meta::identifier_of(^^int); }
    catch (const std::meta::exception&) { return true; }
    return false;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        static_assert(!std::meta::has_identifier(^^int));
        static_assert(guarded_identifier_request());
        std::cout << "invalid metadata request handled during constant evaluation\n";
        std::cout << "OK 21-diagnostics\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
