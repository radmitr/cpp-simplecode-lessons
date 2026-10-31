#include <sstream>
#include <ostream>
#include "../common/check.hpp"

struct CountingBuffer : std::stringbuf { int flushes=0; int sync() override { ++flushes; return 0; } };

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        CountingBuffer buffer;
        std::ostream output(&buffer);
        for(int i=0;i<3;++i) output << i << '\n';
        check(buffer.flushes==0,"newline unexpectedly flushed custom buffer");
        output << std::flush;
        check(buffer.flushes==1,"explicit flush missing");
        for(int i=0;i<3;++i) output << i << std::endl;
        check(buffer.flushes==4,"endl must request flush");
        std::cout << "newline: 0 flushes; explicit flush: 1; three endl: 3\n";
        std::cout << "OK 12-buffering\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
