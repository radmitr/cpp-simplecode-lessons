#include <sstream>
#include <charconv>
#include <string_view>
#include <system_error>
#include <limits>
#include "../common/check.hpp"

long long sum(std::istream& input,int factor) {
    long long total=0;
    for(std::string token; input>>token;) {
        int value=0;
        const auto [end,error]=std::from_chars(token.data(),token.data()+token.size(),value);
        if(error!=std::errc{} || end!=token.data()+token.size()) throw std::invalid_argument("invalid input token");
        if(value < -1000000 || value>1000000) throw std::invalid_argument("input value out of range");
        const auto term=static_cast<long long>(value)*factor;
        if((term>0 && total>std::numeric_limits<long long>::max()-term) ||
           (term<0 && total<std::numeric_limits<long long>::min()-term)) throw std::overflow_error("sum overflow");
        total+=term;
    }
    if(input.bad() || !input.eof()) throw std::invalid_argument("invalid input token");
    return total;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        if(argc==1) {
            std::istringstream sample("1 2 3");
            check(sum(sample,2)==12,"built-in smoke case failed");
            std::cout << "usage: main --scale POSITIVE_INTEGER < numbers.txt\n";
        } else {
            if(argc!=3 || std::string_view(argv[1])!="--scale") throw std::invalid_argument("usage: --scale POSITIVE_INTEGER");
            int factor=0;const std::string_view text=argv[2];
            const auto [end,error]=std::from_chars(text.data(),text.data()+text.size(),factor);
            if(error!=std::errc{} || end!=text.data()+text.size() || factor<1 || factor>1000) throw std::invalid_argument("invalid scale");
            std::cout << sum(std::cin,factor) << '\n';
        }
        if (argc == 1) std::cout << "OK 19-console-tool\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
