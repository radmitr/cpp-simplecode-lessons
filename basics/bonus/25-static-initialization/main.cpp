#include <string>
#include "../common/check.hpp"

constinit int global_count = 7;
const std::string& cached() { static const std::string text = "initialized on first use"; return text; }

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        check(global_count == 7, "constant initialization failed");
        ++global_count;
        check(global_count == 8, "constinit must not imply const");
        check(&cached() == &cached(), "local static must persist");
        std::cout << global_count << ' ' << cached() << '\n';
        std::cout << "OK 25-static-initialization\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
