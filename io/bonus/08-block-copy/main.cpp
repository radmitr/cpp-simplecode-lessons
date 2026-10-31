#include <array>
#include "../common/check.hpp"

#include "../common/workspace.hpp"
void copy_blocks(const std::filesystem::path& source,const std::filesystem::path& target) {
    std::ifstream input(source,std::ios::binary);
    std::ofstream output(target,std::ios::binary|std::ios::trunc);
    if(!input || !output) throw std::runtime_error("cannot open copy files");
    std::array<char,4096> buffer{};
    while(input.read(buffer.data(),buffer.size()) || input.gcount()!=0) {
        output.write(buffer.data(),input.gcount());
        if(!output) throw std::runtime_error("copy write failed");
    }
    if(input.bad() || !input.eof()) throw std::runtime_error("copy read failed");
    output.close(); if(!output) throw std::runtime_error("copy close failed");
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        LessonWorkspace work;
        std::string data(10003,'x'); data.back()='!';
        write_text(work.path()/"source.bin",data);
        copy_blocks(work.path()/"source.bin",work.path()/"copy.bin");
        check(read_text(work.path()/"copy.bin")==data,"block copy lost data");
        write_text(work.path()/"empty.bin","");
        copy_blocks(work.path()/"empty.bin",work.path()/"empty-copy.bin");
        check(read_text(work.path()/"empty-copy.bin").empty(),"empty copy failed");
        std::cout << "10003 bytes and empty file copied\n";
        std::cout << "OK 08-block-copy\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
