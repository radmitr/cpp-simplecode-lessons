// C++26 — средства заголовка <debugging>.
#include <exception>
#include <iostream>
#include <string_view>
#include <version>

#if __has_include(<debugging>)
#include <debugging>
#endif
#if defined(__cpp_lib_debugging)

#include "../../../basics/bonus/common/check.hpp"

int main(int argc, char* argv[])
{
    try
    {
        const bool attached = std::is_debugger_present();
        std::cout << "debugger: " << attached << std::endl;
        std::breakpoint_if_debugging();
        if (argc == 2 && std::string_view(argv[1]) == "--break") std::breakpoint();
        std::cout << "OK modern-example\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
#else
int main()
{
    std::cout << "UNAVAILABLE: io/bonus/25-debugging\n";
    return 77;
}
#endif
