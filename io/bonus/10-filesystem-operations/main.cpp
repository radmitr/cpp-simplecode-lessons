#include <vector>
#include <algorithm>
#include "../common/check.hpp"

#include "../common/workspace.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        LessonWorkspace work;
        const auto nested=work.path()/"nested";
        std::filesystem::create_directory(nested);
        write_text(nested/"a.txt","abc");
        std::filesystem::copy_file(nested/"a.txt",nested/"b.txt");
        std::filesystem::rename(nested/"b.txt",nested/"c.txt");
        check(std::filesystem::file_size(nested/"c.txt")==3,"copy or rename failed");
        std::vector<std::string> names;
        for(const auto& entry:std::filesystem::directory_iterator(nested)) names.push_back(entry.path().filename().string());
        std::sort(names.begin(),names.end());
        check(names==std::vector<std::string>({"a.txt","c.txt"}),"directory contents mismatch");
        std::error_code error;
        std::filesystem::create_symlink(nested/"a.txt",nested/"link.txt",error);
        if(error) std::cout << "symlink unavailable: " << error.message() << '\n';
        else check(std::filesystem::is_symlink(nested/"link.txt"),"symlink missing");
        check(std::filesystem::remove(nested/"c.txt"),"remove failed");
        std::cout << "filesystem operations verified\n";
        std::cout << "OK 10-filesystem-operations\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
