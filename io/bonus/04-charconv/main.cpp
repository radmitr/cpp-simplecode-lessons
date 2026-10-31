#include <charconv>
#include <array>
#include <string_view>
#include <system_error>
#include "../common/check.hpp"

int parse_integer(std::string_view text) {
    if(text.empty()) throw std::invalid_argument("empty integer");
    int value=0;
    auto [end,error]=std::from_chars(text.data(),text.data()+text.size(),value);
    if(error!=std::errc{} || end!=text.data()+text.size()) throw std::invalid_argument("invalid integer");
    return value;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        check(parse_integer("123")==123 && parse_integer("-7")==-7, "valid number rejected");
        for (std::string_view text : {"", "123abc", "999999999999999999999", " 12"}) {
            bool rejected=false;
            try { (void)parse_integer(text); } catch (const std::invalid_argument&) { rejected=true; }
            check(rejected, "invalid input accepted");
        }
        std::array<char,32> buffer{};
        const auto result=std::to_chars(buffer.data(),buffer.data()+buffer.size(),123);
        check(result.ec==std::errc{}, "format failed");
        std::cout << std::string_view(buffer.data(),static_cast<std::size_t>(result.ptr-buffer.data())) << '\n';
        std::cout << "OK 04-charconv\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
