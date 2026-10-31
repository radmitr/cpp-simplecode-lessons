#include <ostream>
#include <streambuf>
#include <ios>
#include "../common/check.hpp"

class FailingBuffer : public std::streambuf {
    int_type overflow(int_type) override { return traits_type::eof(); }
};

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        FailingBuffer buffer;
        std::ostream output(&buffer);
        output << "cannot write";
        check(output.fail(),"write failure not reflected in state");
        output.clear(); output.exceptions(std::ios::badbit|std::ios::failbit);
        bool caught=false;
        try { output << "still cannot write"; }
        catch(const std::ios_base::failure&) { caught=true; }
        check(caught,"exception mask ignored");
        std::cout << "stream failure and exception paths verified\n";
        std::cout << "OK 11-io-errors\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
