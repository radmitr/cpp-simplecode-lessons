#include <format>
#include <print>
#include "../common/check.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        const auto text=std::format("id={:04}, score={:.2f}",7,1.25);
        check(text=="id=0007, score=1.25","format mismatch");
        std::println("{}",text);
        bool caught=false;
        try { (void)std::vformat("{",std::make_format_args()); }
        catch(const std::format_error&) {caught=true;}
        check(caught,"invalid runtime format accepted");
        std::cout << "OK 21-format-and-print\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
