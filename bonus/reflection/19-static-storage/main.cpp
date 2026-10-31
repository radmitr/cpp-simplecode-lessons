#include <vector>
#include "../common/reflection.hpp"



int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[])
{
    try
    {
        constexpr const char* label = std::define_static_string(std::string("generated_") + "name");
        constexpr auto values = std::define_static_array(std::vector<int>{2, 4, 6});
        static_assert(values.size() == 3);
        check(std::string_view(label) == "generated_name" && values[2] == 6, "static storage failed");
        std::cout << label << ' ' << values.size() << '\n';
        std::cout << "OK 19-static-storage\n";
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
