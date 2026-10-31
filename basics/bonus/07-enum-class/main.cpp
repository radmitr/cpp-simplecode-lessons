#include "../common/check.hpp"

enum class Mode : unsigned { none = 0, read = 1, write = 2, execute = 4 };
constexpr unsigned bits(Mode mode) { return static_cast<unsigned>(mode); }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        const Mode mode = Mode::read;
        const unsigned flags = bits(mode) | bits(Mode::write);
        check((flags & bits(Mode::read)) != 0, "read bit missing");
        check((flags & bits(Mode::execute)) == 0, "execute bit unexpected");
        check(bits(Mode::none) == 0, "empty flags expected");
        std::cout << "combined flags=" << flags << '\n';
        std::cout << "OK 07-enum-class\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
