#include "../common/check.hpp"

#include "../common/workspace.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        LessonWorkspace work;
        const auto directory=work.path()/"folder with spaces";
        std::filesystem::create_directory(directory);
        const auto file=directory/std::filesystem::u8path(u8"данные.txt");
        write_text(file,"payload");
        check(read_text(file)=="payload","Unicode path failed");
        check(file.extension()==".txt" && file.is_absolute(),"path decomposition failed");
        check(file.lexically_relative(work.path()).parent_path()=="folder with spaces","relative path failed");
        std::cout << "Unicode filename opened through filesystem::path\n";
        std::cout << "OK 09-filesystem-path\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
