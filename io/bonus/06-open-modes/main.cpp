#include "../common/check.hpp"

#include "../common/workspace.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        LessonWorkspace work; const auto file=work.path()/"modes.txt";
        write_text(file,"abc");
        { std::ofstream out(file,std::ios::app); out << 'd'; check(static_cast<bool>(out),"append failed"); }
        check(read_text(file)=="abcd","app must preserve data");
        { std::fstream io(file,std::ios::in|std::ios::out|std::ios::ate); io.seekp(0); io << 'X'; check(static_cast<bool>(io),"ate write failed"); }
        check(read_text(file)=="Xbcd","ate must allow repositioning");
        { std::ofstream out(file,std::ios::trunc); out << 'z'; }
        check(read_text(file)=="z","trunc must discard previous contents");
        std::cout << "app appends; ate starts at end; trunc replaces\n";
        std::cout << "OK 06-open-modes\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
