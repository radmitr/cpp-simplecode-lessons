#include <sstream>
#include <limits>
#include <charconv>
#include <string>
#include <system_error>
#include "../common/check.hpp"

int sum_numbers(std::istream& input) {
    int total=0;
    for (std::string token; input >> token;) {
        int value=0;
        const auto [end,error]=std::from_chars(token.data(),token.data()+token.size(),value);
        if(error!=std::errc{} || end!=token.data()+token.size()) throw std::runtime_error("invalid number token");
        if((value>0 && total>std::numeric_limits<int>::max()-value) ||
           (value<0 && total<std::numeric_limits<int>::min()-value)) throw std::runtime_error("sum overflow");
        total+=value;
    }
    if(input.bad() || !input.eof()) throw std::runtime_error("invalid number stream");
    return total;
}
void report(std::ostream& output,int value) {output << "sum=" << value << '\n';if(!output) throw std::runtime_error("report failed");}
struct Redirect {
    std::ostream& stream;std::streambuf* old;
    Redirect(std::ostream& out,std::streambuf* replacement):stream(out),old(out.rdbuf(replacement)){}
    ~Redirect(){stream.rdbuf(old);}
    Redirect(const Redirect&)=delete;Redirect& operator=(const Redirect&)=delete;
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        std::istringstream input("1 2 3");
        std::ostringstream output;
        const auto total=sum_numbers(input);
        report(output,total);
        check(total==6 && output.str()=="sum=6\n","stream abstraction failed");
        bool rejected=false;
        try { std::istringstream bad("1 999999999999999999999"); (void)sum_numbers(bad); }
        catch(const std::runtime_error&) {rejected=true;}
        check(rejected,"overflowing final token was mistaken for normal EOF");
        std::ostringstream redirected;
        { Redirect guard(output,redirected.rdbuf()); output << "redirected"; }
        output << "restored";
        check(redirected.str()=="redirected" && output.str()=="sum=6\nrestored","rdbuf restoration failed");
        std::cout << "same functions accept strings, files and console streams\n";
        std::cout << "OK 18-stream-interfaces\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
