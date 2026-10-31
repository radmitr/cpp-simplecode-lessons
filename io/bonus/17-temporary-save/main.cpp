#include <system_error>
#include "../common/check.hpp"

#include "../common/workspace.hpp"
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif
void save_checked(const std::filesystem::path& target,const std::string& text,bool valid) {
    const auto temporary=target.parent_path()/"prepared.tmp";
    if(std::filesystem::exists(temporary)) throw std::runtime_error("temporary already exists");
    try {
        write_text(temporary,text);
        if(!valid) throw std::runtime_error("validation failed");
#ifdef _WIN32
        if(!MoveFileExW(temporary.c_str(),target.c_str(),MOVEFILE_REPLACE_EXISTING))
            throw std::system_error(static_cast<int>(GetLastError()),std::system_category(),"replace failed");
#else
        std::filesystem::rename(temporary,target);
#endif
    } catch(...) {std::error_code ignored;std::filesystem::remove(temporary,ignored);throw;}
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        LessonWorkspace work;const auto target=work.path()/"settings.txt";
        write_text(target,"old");
        bool rejected=false;
        try {save_checked(target,"invalid",false);} catch(const std::runtime_error&) {rejected=true;}
        check(rejected && read_text(target)=="old","failed preparation damaged original");
        save_checked(target,"new",true);
        check(read_text(target)=="new","replacement failed");
        std::cout << "prepare, close, validate, replace\n";
        std::cout << "OK 17-temporary-save\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
