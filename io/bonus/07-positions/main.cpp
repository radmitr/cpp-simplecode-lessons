#include "../common/check.hpp"

#include "../common/workspace.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        LessonWorkspace work; const auto file=work.path()/"positions.bin";
        write_text(file,"abcdef");
        std::fstream stream(file,std::ios::in|std::ios::out|std::ios::binary);
        stream.seekg(2); char value=0; stream.get(value);
        check(value=='c' && stream.tellg()==std::streampos(3),"get position mismatch");
        stream.seekp(1); stream.put('X'); stream.flush();
        check(static_cast<bool>(stream),"positioned write failed");
        stream.seekg(0);
        std::string all; std::getline(stream,all);
        check(all=="aXcdef","read/write switch failed");
        stream.clear(); stream.seekg(0); stream.get(value);
        check(value=='a',"rewind after EOF failed");
        std::cout << all << '\n';
        std::cout << "OK 07-positions\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
