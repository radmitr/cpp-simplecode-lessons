#include <sstream>
#include <iomanip>
#include <string>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        std::ostringstream out;
        const auto flags=out.flags(); const auto precision=out.precision(); const auto fill=out.fill();
        out << std::fixed << std::setprecision(2) << 1.25 << ' ' << std::setw(4) << std::setfill('0') << 7;
        check(out.str()=="1.25 0007", "format mismatch");
        out.flags(flags); out.precision(precision); out.fill(fill);
        std::string text="two words and \"quotes\"";
        std::stringstream roundtrip;
        roundtrip << std::quoted(text);
        std::string restored; roundtrip >> std::quoted(restored);
        check(restored==text, "quoted string round trip failed");
        std::cout << out.str() << '\n';
        std::cout << "OK 05-iomanip\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
